#ifndef Item_JOUKE
#define Item_JOUKE

#include "zmqClient.hpp"
#include "adresses.hpp"

using namespace std;

/*! -------------------------------------------------------------
* brief   Item class
* details
* author  Jouke Hijlkema (jouke.hijlkema@onera.fr)
* date    Date
* version 1.0
*
* -------------------------------------------------------------*/
class Item {
public:

  Item();
  ~Item();
  zmqClient *com;
  void parse();

  bool quit = false;

protected:

private:

};
#endif
