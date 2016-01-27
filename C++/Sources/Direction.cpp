#include "Direction.hpp"

#include <algorithm>
#include "Tools.hpp"
#include <unistd.h>
#ifdef rpi
#include <wiringPi.h>
#endif

/* ==============================================================
 * Description : Direction class
 * initial version : 1.0
 * Author : hylkema (jouke.hijlkema@onera.fr)
 * date   :
 * ============================================================== */
Direction::Direction() {
  this->com = new zmqClient("Direction","Direction",LOCAL_OUT,LOCAL_IN,SUB_PUSH);
#ifdef rpi
  wiringPiSetupPhys();
  pinMode (DirPin, OUTPUT);
  pinMode (StepPin, OUTPUT);
  digitalWrite(DirPin,LOW);
  Spi.sendString("0000 0000 0000 0000 0110"); //DRVCTRL
  Spi.sendString("1001 0000 0001 1011 0100"); //chopconf
  Spi.sendString("1010 0010 0010 0000 0010"); //coolstep
  Spi.sendString("1101 0111 1111 0000 0000"); //Stallguard
  Spi.sendString("1110 0000 0000 0000 0000"); //DRVCONF

#endif
}

Direction::~Direction() {
}
/**
 * do a number of steps with a given setSpeed
 * @param steps number of steps, negative changes direction
 * @param speed speed (between -100 and 100)
 */
void Direction::Step(int steps, int speed) {
  std::cout << "stepping "<<steps<<"x"<<speed<<" ..." << std::endl;
#ifdef rpi
  if (speed<0) {
    digitalWrite(DirPin,HIGH);
  } else  {
    digitalWrite(DirPin,LOW);
  }
  speed = abs(speed);
  int pw = 1000 - round(9.5 * speed);
  for (int i = 0; i < steps; i++) {
    digitalWrite(StepPin,HIGH);
    usleep(pw);
    digitalWrite(StepPin,LOW);
    usleep(pw);
  }
#endif
}
/**
 * parse an order
 */
void Direction::parse() {
  Item::parse();
  std::cout << "parsing ..." << std::endl;
  if (this->com->got("Direction","Steps",false)) {
    string order = this->com->get("Direction","Steps");
    string steps = token(order,2,false);
    string speed = token(order,3,false);
    this->Step(stoi(steps),stoi(speed));
  }
}
// ========================================================================
// === Main
// ========================================================================
int main(int argc, char const *argv[]) {
  Direction myDirection;
  myDirection.com->send("Grasmaaier:Direction:Online");
  while (1) {
    myDirection.com->receive();
    myDirection.parse();
    if (myDirection.quit) break;
  }
}
