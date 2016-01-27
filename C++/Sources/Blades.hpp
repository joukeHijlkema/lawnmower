#ifndef Blades_JOUKE
#define Blades_JOUKE

#include "Item.hpp"

using namespace std;

/*! -------------------------------------------------------------
 * brief   Blades class
 * details
 * author  Jouke Hijlkema (jouke.hijlkema@onera.fr)
 * date    Date
 * version 1.0
 *
 * -------------------------------------------------------------*/
class Blades : public Item {
public:

  Blades();
  ~Blades();

  void parse();


protected:

private:

  int startStop = 2;
  int dir = 3;

};
#endif
