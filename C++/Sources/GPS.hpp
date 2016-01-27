#ifndef GPS_JOUKE
#define GPS_JOUKE

#include "Item.hpp"

/*! -------------------------------------------------------------
 * brief   GPS class
 * details
 * author  Jouke Hijlkema (jouke.hijlkema@onera.fr)
 * date    Date
 * version 1.0
 *
 * -------------------------------------------------------------*/
class GPS:public Item {
public:

  GPS();
  ~GPS();

  void parse();

protected:

private:


};
#endif
