#ifndef Direction_JOUKE
#define Direction_JOUKE

#include "mySpi.hpp"
#include "Item.hpp"

using namespace std;

/*! -------------------------------------------------------------
* brief   Direction class
* details
* author  Jouke Hijlkema (jouke.hijlkema@onera.fr)
* date    Date
* version 1.0
*
* -------------------------------------------------------------*/
class Direction:public Item {
public:

  Direction();
  ~Direction();

  void Step(int steps, int speed);
  void parse();

protected:

private:

  mySpi Spi;
  int   DirPin  = 31;
  int   StepPin = 33;

};
#endif
