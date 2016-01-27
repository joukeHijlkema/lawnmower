#ifndef GpsBase_JOUKE
#define GpsBase_JOUKE

#include "Item.hpp"
#include "mySql.hpp"
#include <libgpsmm.h>

using namespace std;

/*! -------------------------------------------------------------
 * brief   GpsBase class
 * details
 * author  Jouke Hijlkema (jouke.hijlkema@onera.fr)
 * date    Date
 * version 1.0
 *
 * -------------------------------------------------------------*/
class GpsBase : public Item {
public:

  GpsBase();
  ~GpsBase();

  void parse();
  void readGps();

protected:

private:
  mySql *db;
  gpsmm *gps_rec;
  long double fixedLat = 43.1687083662450700000000;
  long double fixedLon = 1.1919731893782597000000;
};
#endif
