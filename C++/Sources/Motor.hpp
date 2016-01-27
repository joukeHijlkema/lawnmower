#ifndef Motor_JOUKE
#define Motor_JOUKE

#include "Item.hpp"
#ifdef rpi
#include <wiringPi.h>
#endif

/*! -------------------------------------------------------------
* brief   Motor class
* details
* author  Jouke Hijlkema (jouke.hijlkema@onera.fr)
* date    Date
* version 1.0
*
* -------------------------------------------------------------*/
class Motor : public Item {
public:

  Motor();
  ~Motor();
  
  void parse();

protected:

private:

  int startStop = 2;
  int dir       = 3;

};
#endif
