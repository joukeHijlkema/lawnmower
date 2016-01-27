#include "Motor.hpp"
#ifdef rpi
#include <wiringPi.h>
#endif
/* ==============================================================
 * Description : Motor class
 * initial version : 1.0
 * Author : hylkema (jouke.hijlkema@onera.fr)
 * date   :
 * ============================================================== */
Motor::Motor() {
  this->com = new zmqClient("Motor","Motor",LOCAL_OUT,LOCAL_IN,SUB_PUSH);
#ifdef rpi
  wiringPiSetup ();
  pinMode (startStop, OUTPUT);
  pinMode (dir, OUTPUT);
#endif
}

Motor::~Motor() {

}

/**
 * Parse a received message
 */
void Motor::parse() {
  Item::parse();
  if (this->com->got("Motor","Stop")) {
    std::cout << "Stop motor" << std::endl;
#ifdef rpi
    digitalWrite (startStop, LOW);
#endif
  } else if (this->com->got("Motor","Start")) {
    std::cout << "Start motor" << std::endl;
#ifdef rpi
    digitalWrite (startStop, HIGH);
#endif
  } else if (this->com->got("Motor","SetSpeed",false)) {
    int speed = this->com->getInt("Motor","SetSpeed");
    std::cout << "Set speed to " << speed << std::endl;
#ifdef rpi
    // set the motor speed
#endif
  }
}
// ========================================================================
// === Main
// ========================================================================
int main(int argc, char const *argv[]) {
  Motor myMotor;
  myMotor.com->send("Grasmaaier:Motor:Online");
  while (1) {
    myMotor.com->receive();
    myMotor.parse();
    if (myMotor.quit) break;
  }
}
