/**
 * Switch off the rpi from afar
 */
#include "zmqClient.hpp"
#include "ipinfo.hpp"

using namespace std;

int main(int argc, char *argv[]) {

  ipinfo    *IP = new ipinfo();
  zmqClient client("general",IP->ip);

  while(true) {

    // Receive (blocking call)
    client.globalReceive();
    if (client.token(2)=="ShutDown") {
      cout << "shut down now\n";
      client.send("Shutting down now ...");
      #ifdef rpi
      system("shutdown -h now	");
      #endif
    }
  }
  return 0;
}
