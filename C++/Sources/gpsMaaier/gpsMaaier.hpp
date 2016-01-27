#ifndef gpsMaaier_JOUKE
#define gpsMaaier_JOUKE

#include "Item.hpp"
#include "mySql.hpp"
#include <libgpsmm.h>

using namespace std;
/*! -------------------------------------------------------------
* brief   gpsMaaier class
* details
* author  Jouke Hijlkema (jouke.hijlkema@onera.fr)
* date    Date
* version 1.0
*
* -------------------------------------------------------------*/
class gpsMaaier : public Item {
public:
  gpsMaaier();
  ~gpsMaaier();

  void parse();
  void readGps();

protected:
private:
  mySql  *db;
  gpsmm  *gps_rec;
  long double errorLat = 0.0;
  long double errorLon = 0.0;
  long double errorVit = 0.0;
};
#endif
