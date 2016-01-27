#ifndef grasmaaier_JOUKE
#define grasmaaier_JOUKE

#include "zmqClient.hpp"
#include "adresses.hpp"
#include <string>
#include <zmqpp/zmqpp.hpp>


/*! -------------------------------------------------------------
* brief   grasmaaier class
* details
* author  Jouke Hijlkema (jouke.hijlkema@onera.fr)
* date    Date
* version 1.0
*
* -------------------------------------------------------------*/

class grasmaaier {

public:

  grasmaaier();
  ~grasmaaier();

  void parse(string msg);
  void localParse(string msg);
  void parseDirection(string msg);
  void parseMotor(string msg);
  void parseBlades(string msg);
  void parseGlobal(string msg);

  zmqClient *pilotCom,*localCom;
  zmqpp::poller *myPoller;

protected:

private:



};
#endif
