#include "GPS.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#ifdef rpi
#include <libgpsmm.h>
#endif

/* ==============================================================
 * Description : GPS class
 * initial version : 1.0
 * Author : hylkema (jouke.hijlkema@onera.fr)
 * date   :
 * ============================================================== */
GPS::GPS() {
  this->com = new zmqClient("GPS","GPS",LOCAL_OUT,LOCAL_IN,SUB_PUSH);
}

GPS::~GPS() {
}
/**
 * parse a message
 * @author Jouke Hijlkema
 * @date   2015-10-13T13:36:08+020
 */
void GPS::parse() {
  Item::parse();
}

int main(int argc, char const *argv[]) {
  GPS myGPS;
  myGPS.com->send("Grasmaaier:GPS:Online");

#ifdef rpi
  gpsmm gps_rec("localhost", DEFAULT_GPSD_PORT);
  ostringstream out;

  if (gps_rec.stream(WATCH_ENABLE | WATCH_JSON) == NULL) {
    cerr << "No GPSD running.\n";
    return 1;
  }

  for (;; ) {
    struct gps_data_t * newdata;

    if (!gps_rec.waiting(50000000))
      continue;

    if ((newdata = gps_rec.read()) == NULL) {
      cerr << "Read error.\n";
      return 1;
    } else {
      out<<"position:"<< setprecision(20) << newdata->fix.latitude <<","<<newdata->fix.longitude<< "\n";
      myGPS.com->send(out.str());
    }
  }
  #endif
  while (1) {
    myGPS.com->receive();
    myGPS.parse();
    if (myGPS.quit) break;
  }
}
