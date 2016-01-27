#include "zmqClient.hpp"
int main(int argc, char const *argv[]) {

  zmqClient client("Battery");
  // Wait for a ping and say hello
  while(true) {
    if (client.receiveNb()) {
      // std::cout << "received : " << client.getMessage() << std::endl;
      if (client.token(2)=="ping") {
        std::cout << "running" << std::endl;
        client.send("Battery running");
        break;
      }
    }
  }
  client.disconnect();
  return 0;
}
