#include "grasmaaier.hpp"
#include "adresses.hpp"
#include <unistd.h>
#include "Tools.hpp"

/* ==============================================================
 * Description : grasmaaier class
 * initial version : 1.0
 * Author : hylkema (jouke.hijlkema@onera.fr)
 * date   :
 * ============================================================== */
grasmaaier::grasmaaier() {
  this->pilotCom = new zmqClient("Grasmaaier","Grasmaaier",PILOT_IN,PILOT_OUT,SUB_PUSH);
  this->localCom = new zmqClient("","Grasmaaier",LOCAL_IN,LOCAL_OUT,PUB_PULL);
  this->myPoller = new zmqpp::poller();
  this->myPoller->add(*(this->pilotCom->getInSocket()));
  this->myPoller->add(*(this->localCom->getInSocket()));
}

grasmaaier::~grasmaaier() {
}

/**
 * Parse a message
 * @author Jouke Hijlkema
 * @date   2015-10-13T12:02:47+020
 * @param  msg                     the message to parse
 */
void grasmaaier::parse(string msg) {
  std::cout << "/* message */ "<<msg << std::endl;
  string target  = token(msg,1,false);
  string message = token(msg,2,true);
  std::cout << "Parse : " << message << " -> " << target << std::endl;
  if (target=="Motor") this->parseMotor(message);
  if (target=="Blades") this->parseBlades(message);
  if (target=="Global") this->parseGlobal(message);
  if (target=="Direction") this->parseDirection(message);
}
/**
 * Act on a direction message
 * @author Jouke Hijlkema
 * @date   2015-10-13T12:12:22+020
 * @param  msg                     the message
 */
void grasmaaier::parseDirection(string msg) {
  // for now just send the message to the locals
  this->localCom->send("Direction:" + msg);
}
/**
 * Act on a motor message
 * @author Jouke Hijlkema
 * @date   2015-10-13T12:12:22+020
 * @param  msg                     the message
 */
void grasmaaier::parseMotor(string msg) {
  // for now just send the message to the locals
  this->localCom->send("Motor:" + msg);
}
/**
 * Act on a blades message
 * @author Jouke Hijlkema
 * @date   2015-10-13T12:12:22+020
 * @param  msg                     the message
 */
void grasmaaier::parseBlades(string msg) {
  // for now just send the message to the locals
  this->localCom->send("Blades:" + msg);
}
/**
 * Act on a global message
 * @author Jouke Hijlkema
 * @date   2015-10-13T12:12:22+020
 * @param  msg                     the message
 */
void grasmaaier::parseGlobal(string msg) {
  // for now just send the message to the locals
  this->localCom->send("Global:" + msg);
}
/**
 * parse a message from the localParse
 * @author Jouke Hijlkema
 * @date   2015-10-13T14:00:14+020
 * @param  msg                     the message
 */
void grasmaaier::localParse(string msg) {
  string target  = token(msg,1,false);
  string message = token(msg,2,true);
  std::cout << "target = " << target << std::endl;
  std::cout << "message = " << message << std::endl;
  if (message=="Online") {
    this->pilotCom->send(msg);
  }

  if (message=="msg);
  }

}
// ========================================================================
// === Main
// ========================================================================
int main(int argc, char *argv[]) {
  grasmaaier myGrasmaaier;

  // start the event loop
  while (1) {
    std::cout << "waiting on " << PILOT_OUT << " & " << LOCAL_IN << "... " << std::endl;
    if (myGrasmaaier.myPoller->poll()) {
      if(myGrasmaaier.myPoller->has_input(*(myGrasmaaier.pilotCom->getInSocket()))) {
        myGrasmaaier.pilotCom->receive();
        for (auto s : myGrasmaaier.pilotCom->getMessages()) {
          myGrasmaaier.parse(s);
        }
      }
      if(myGrasmaaier.myPoller->has_input(*(myGrasmaaier.localCom->getInSocket()))) {
        std::cout << "received a message from a local" << std::endl;
        myGrasmaaier.localCom->receive();
        for (auto s : myGrasmaaier.localCom->getMessages()) {
          myGrasmaaier.localParse(s);
        }
      }
    }
  }
  string quit = "";
  while (quit!="q") {
    std::cout << std::endl << "? : ";
    std::cin >> quit;
    myGrasmaaier.localCom->send(quit);
  }
}
