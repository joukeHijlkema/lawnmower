#include "zmqClient.hpp"
#include <iostream>
#include <utility>
#include "Tools.hpp"

zmqClient::zmqClient(
  string channel,
  string name,
  string _AdIn,
  string _AdOut,
  type t) {

  this->Name  = name;
  this->AdIn  = _AdIn;
  this->AdOut = _AdOut;
  delimiter   = ":";

  switch (t) {
  case SUB_PUSH:

    In = new zmqpp::socket(context, zmqpp::socket_type::subscribe);
    In->subscribe(channel);
    In->subscribe("Global");
    cout << "Subscribing to in SUB " << AdIn << " channel Global and '" << channel << "' ..." << endl;
    In->connect(AdIn);

    Out = new zmqpp::socket(context, zmqpp::socket_type::push);
    cout << "Connecting to out PUSH " << AdOut << "' ..." << endl;
    Out->connect(AdOut);

    break;

  case PUB_PULL:
    In = new zmqpp::socket(context, zmqpp::socket_type::pull);
    cout << "Binding to in PULL " << AdIn << "' ..." << endl;
    In->bind(AdIn);

    Out = new zmqpp::socket(context, zmqpp::socket_type::publish);
    cout << "Binding to out PUB " << AdOut << "' ..." << endl;
    Out->bind(AdOut);
    break;
  }
  pol.add(*In);
  sleep(1);       // wait for connection to stableise

}

zmqClient::~zmqClient() {
}
/**
 * get the first element from a line
 * @return the key
 */
string zmqClient::key() {
  return token(this->msg.get(0),1,false);
}
/**
 * return the value after the key from a line
 * @return the value
 */
string zmqClient::value() {
  return token(this->msg.get(0),2,true);
}
/**
 * wait for a message
 * @author Jouke Hijlkema
 * @date   2015-10-02T17:46:26+020
 */
void zmqClient::receive() {
  std::cout << "waiting on " << AdIn << "..." << std::endl;
  this->In->receive(this->msg);
  this->storeMsg();
}
/**
 * return true if we received a message
 * @author Jouke Hijlkema
 * @date   2015-10-02T17:47:15+020
 * @return [description]
 */
bool zmqClient::receiveNb() {
  if (pol.poll(10)) {
    this->In->receive(this->msg);
    this->storeMsg();
    return true;
  }
  return false;
}
/**
 * [zmqClient::storeMsg description]
 */
void zmqClient::storeMsg() {
  pair<string,string> res = make_pair<string,string>(key(),value());
  std::cout << "received : " << res.second << " for " << res.first << std::endl;
  Messages.insert(res);
  std::cout << "Message size = " <<Messages.size()<< std::endl;
  std::cout << "ZMG msg parts = " << this->msg.parts() << std::endl;
  std::cout << "ZMG msg size  = " << this->msg.size(0) << std::endl;
  while (this->msg.parts()>0) this->msg.pop_back();
}
/**
 * send a msg over the connection
 * @author Jouke Hijlkema
 * @date   2015-10-02T09:19:07+020
 * @param  msg                     the message to send
 */
void zmqClient::send(string out) {
  cout << "sending on " << AdOut << ": " << out << " .... ";
  this->Out->send(out);
  std::cout << "done" << std::endl;
}
/**
 * disconnect
 * @author Jouke Hijlkema
 * @date   2015-10-02T17:54:29+020
 */
void zmqClient::disconnect() {
  this->In->disconnect(this->AdIn);
  this->Out->disconnect(this->AdOut);
}
/**
 * return the last message received.
 * @author Jouke Hijlkema
 * @date   2015-10-02T17:55:17+020
 * @param  params                  [description]
 * @return                         [description]
 */
vector<string> zmqClient::getMessages() {
  vector<string> out;
  for (auto s : this->Messages) {
    out.push_back(s.second);
  }
  this->Messages.clear();
  return out;
}
/**
 * return true if we've recieved msg, remove it from the stack if erase is true
 * @param  key   the sender
 * @param  msg   the message
 * @param  erase erase ore Notation
 * @return       recevied or not
 */
bool zmqClient::got(string key,string msg,bool erase) {
  string msgFound = this->get(key,msg,erase);
  string subKey   = token(msgFound,1,false);
  return (subKey == msg);
}
/**
 * return a message we've received
 * @author Jouke Hijlkema
 * @date   2015-10-13T13:03:45+020
 * @param  key                     [description]
 * @param  msg                     [description]
 * @param  erase                   [description]
 * @return                         [description]
 */
string zmqClient::get(string key,string msg,bool erase) {
  string subKey;
  string out = "NotFound";
  if (this->Messages.size()>0) {
    auto range = this->Messages.equal_range(key);
    for (auto i = range.first; i!=range.second; i++) {
      subKey = token(i->second,1,false);
      if (subKey == msg) {
        out = i->second;
        if (erase) this->Messages.erase(i);
        break;
      }
    }
  }
  return out;
}
int zmqClient::getInt(string key,string msg,bool erase) {
  string msgFound = this->get(key,msg,erase);
  if (msgFound=="NotFound") return 0;
  string value = token(msgFound,2,false);
  return stoi(value);
}
