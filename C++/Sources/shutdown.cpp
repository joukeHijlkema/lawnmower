#include <zmqpp/zmqpp.hpp>
#include <string>
#include <iostream>
#include <unistd.h>

int main(int argc, char const *argv[]) {

  std::string AD = "tcp://*:4245";
  zmqpp::context context;
  zmqpp::socket myOutput(context, zmqpp::socket_type::publish);
  myOutput.bind(AD);
  // This is SUPER important to wait for the connection to be established !!
  // once the ping function works we might use that
  sleep(1);

  zmqpp::message message;
  message << "global ShutDown";
  myOutput.send(message);
  std::cout << "broadcast kill signal on "<<AD << std::endl;
  sleep(1);

  // myOutput.disconnect(AD);

  return 0;
}
