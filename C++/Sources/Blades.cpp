#include "Blades.hpp"
#ifdef rpi
#include <wiringPi.h>
#endif
/* ==============================================================
 * Description : Blades class
 * initial version : 1.0
 * Author : hylkema (jouke.hijlkema@onera.fr)
 * date   :
 * ============================================================== */
Blades::Blades() {
  this->com = new zmqClient("Blades","Blades",LOCAL_OUT,LOCAL_IN,SUB_PUSH);
}

Blades::~Blades() {
}

/**
 * parse a message
 * @author Jouke Hijlkema
 * @date   2015-10-13T13:36:08+020
 */
void Blades::parse() {
  Item::parse();
  if (this->com->got("Blades","Stop")) {
    std::cout << "Stop blades" << std::endl;
#ifdef rpi
    digitalWrite (startStop, LOW);
#endif
  } else if (this->com->got("Blades","Start")) {
    std::cout << "Start blades" << std::endl;
#ifdef rpi
    digitalWrite (startStop, HIGH);
#endif
  }
}


// ========================================================================
// === Main
// ========================================================================
int main(int argc, char const *argv[]) {
  Blades myBlades;
  myBlades.com->send("Grasmaaier:Blades:Online");
  while (1) {
    myBlades.com->receive();
    myBlades.parse();
    if (myBlades.quit) break;
  }
}
