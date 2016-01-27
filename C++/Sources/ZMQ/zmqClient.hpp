#ifndef jouke_zmqClient
#define jouke_zmqClient

#include <zmqpp/zmqpp.hpp>
#include <string>
#include <unordered_map>
#include <unistd.h>


using namespace std;

enum type {SUB_PUSH,PUB_PULL};

class zmqClient {
public:

  zmqClient(string channel,string name,string _AdIn,string _AdOut, type t);
  ~zmqClient();
  string         key();
  string         value();
  void           receive();
  bool           receiveNb();
  void           storeMsg();
  void           send(string msg);
  vector<string> getMessages();
  void           disconnect();
  bool           got(string key,string msg,bool erase = true);
  string         get(string key,string msg,bool erase = true);
  int            getInt(string key,string msg,bool erase = true);
  zmqpp::socket *getInSocket() {return In; };
  string         getName()     {return this->Name; };


private:

  string                            delimiter;
  zmqpp::context                    context;
  zmqpp::socket                     *In,*Out;
  zmqpp::message                    msg;
  string                            Name,AdIn,AdOut;
  unordered_multimap<string,string> Messages;
  zmqpp::poller pol;;

};
#endif
