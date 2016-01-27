#include "Battery.hpp"
#include <wiringPi.h>
#include <sstream>
#include <unistd.h>
/* ==============================================================
 * Description : Battery class
 * initial version : 1.0
 * Author : hylkema (jouke.hijlkema@onera.fr)
 * date   :
 * ============================================================== */
Battery::Battery() {
  this->com = new zmqClient("Battery","Battery",LOCAL_OUT,LOCAL_IN,SUB_PUSH);
  wiringPiSetupPhys();
  pinMode (High, INPUT);
  pinMode (Medium, INPUT);
  pinMode (Low, INPUT);
}

Battery::~Battery() {
}

/**
 * parse a message
 * @author Jouke Hijlkema
 * @date   2015-10-13T13:36:08+020
 */
void Battery::parse() {
  Item::parse();

}
/**
 * [Battery::Status description]
 * @return [description]
 */
string Battery::Status() {
  stringstream out;
  out  << "Status:" << digitalRead(High) << digitalRead(Medium) << digitalRead(Low) << "\n";
  return out.str();
}

int main(int argc, char const *argv[]) {
  Battery myBattery;
  myBattery.com->send("Grasmaaier:Battery:Online");

  while (1) {
    if (myBattery.com->receiveNb()) {
      myBattery.parse();
    }
    if (myBattery.quit) {
      break;
    }
    myBattery.com->send("Grasmaaier:Battery:"+myBattery.Status());
    sleep(5);
  }
}
