#include "gpsMaaier.hpp"
#include "Tools.hpp"

#include <cmath>
#include <unistd.h>

/* ==============================================================
 * Description : gpsMaaier class
 * initial version : 1.0
 * Author : hylkema (jouke.hijlkema@onera.fr)
 * date   :
 * ============================================================== */
gpsMaaier::gpsMaaier() {
  this->com     = new zmqClient("GpsMaaier","GpsMaaier",PILOT_IN,PILOT_OUT,SUB_PUSH);
  db            = new mySql();
  this->gps_rec = new gpsmm("localhost", DEFAULT_GPSD_PORT);
  if (gps_rec->stream(WATCH_ENABLE | WATCH_JSON) == NULL) {
    cerr << "No GPSD running.\n";
    exit(1);
  }
}
gpsMaaier::~gpsMaaier() {
}
/**
 * Parse messages
 * @author Jouke Hijlkema
 * @date   2016-01-02T23:12:39+010
 */
void gpsMaaier::parse() {
  Item::parse();
}
/**
 * read the GPS data
 * @author Jouke Hijlkema
 * @date   2016-01-02T23:52:31+010
 */
void gpsMaaier::readGps() {
  ostringstream     sql;
  long double       lat,lon,alt,vit;
  char              scr[128];
  string            timeString;
  long long         time;
  struct gps_data_t *newdata;
  if (!this->gps_rec->waiting(50000)) return;

  if ((newdata = this->gps_rec->read()) == NULL) {
    cout << "Read error.\n";
    return;
  } else {
    lat = newdata->fix.latitude;
    lon = newdata->fix.longitude;
    alt = newdata->fix.altitude;
    vit = newdata->fix.speed;

    (void)unix_to_iso8601(newdata->fix.time, scr, sizeof(scr));
    time = timecode(scr);
    std::cout << time << "\n";

    if (lat != lat || lon != lon || alt != alt|| vit != vit) {
      std::cout << "no valid gps data" << std::endl;
      return;
    }
    std::cout << "\n####################################" << std::endl;
    sql.str("");
    sql.clear();
    sql << setprecision(20) << "SELECT errorLat,errorLon,Vit FROM GpsBase WHERE Time=" << time;
    usleep(50000); // to make sure the base has send its data
    vector<long double> out = this->db->getLongDoubles(sql.str());
    if (out.size()>0) {
      this->errorLat = out.at(0);
      this->errorLon = out.at(1);
      this->errorVit = out.at(2);
    } else  {
      std::cout << "!!!!!!!!! No base information !!! use old correction" << std::endl;
    }
    std::cout << setprecision(20)<< "gps        : " << lat                  << "," << lon                  << "," << vit << std::endl;
    std::cout << setprecision(20)<< "correction : " << lat - this->errorLat << "," << lon - this->errorLat << "," << vit - this->errorVit << std::endl;

    sql.str("");
    sql.clear();
    sql << setprecision(20) << "REPLACE INTO Maaier (TIME,LAT,LON,ALT,VIT) VALUES (";
    sql << time << "," << lat - this->errorLat << "," << lon - this->errorLon << "," << alt << "," << vit - this->errorVit << ")";
    this->db->Query(sql.str());

  }
}

int main(int argc, char const *argv[]) {

  gpsMaaier myGpsMaaier;

  while (1) {
    if (myGpsMaaier.com->receiveNb()) {
      myGpsMaaier.parse();
    }
    myGpsMaaier.readGps();
    if (myGpsMaaier.quit) {
      break;
    }
  }
}
