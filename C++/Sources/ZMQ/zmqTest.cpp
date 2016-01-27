#include "zmqTest.hpp"
/* ==============================================================
 * Description : zmqTest class
 * initial version : 1.0
 * Author : hylkema (jouke.hijlkema@onera.fr)
 * date   :
 * ============================================================== */
zmqTest::zmqTest() {
  this->com = new zmqClient("zmqTest","zmqTest",PILOT_IN,PILOT_OUT,SUB_PUSH);
  this->com->send("zmqTest:Online");
}
zmqTest::~zmqTest() {
}

int main(int argc, char const *argv[]) {
  /* code */
  zmqTest myTest;
  while (!myTest.quit) {
    if (myTest.com->receiveNb()) {
      myTest.parse();
    }
  }
  exit(0);
}
