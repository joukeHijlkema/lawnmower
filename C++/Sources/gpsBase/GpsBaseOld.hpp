#ifndef GpsBase_JOUKE
#define GpsBase_JOUKE

#include "Item.hpp"
#include "Database.hpp"
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

  void sendUpdate();

protected:

private:

  Database *db;
  gpsmm *gps_rec;

};
#endif
