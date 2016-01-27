#include "GpsBase.hpp"
#include "Tools.hpp"
/* ==============================================================
 * Description : GpsBase class
 * initial version : 1.0
 * Author : hylkema (jouke.hijlkema@onera.fr)
 * date   :
 * ============================================================== */
GpsBase::GpsBase() {
  this->com     = new zmqClient("GpsBase","GpsBase",PILOT_IN,PILOT_OUT,SUB_PUSH);
  db            = new mySql();
  this->gps_rec = new gpsmm("localhost", DEFAULT_GPSD_PORT);
  if (gps_rec->stream(WATCH_ENABLE | WATCH_JSON) == NULL) {
    cerr << "No GPSD running.\n";
    exit(1);
  }
}

GpsBase::~GpsBase() {
}
/**
 * Parse messages
 * @author Jouke Hijlkema
 * @date   2016-01-02T23:12:39+010
 */
void GpsBase::parse() {
  Item::parse();

  // if (this->com->got("GpsBase","Update")) this->sendUpdate();

}
/**
 * read the GPS data
 * @author Jouke Hijlkema
 * @date   2016-01-02T23:52:31+010
 */
void GpsBase::readGps() {
  ostringstream     sql;
  long double       lat,lon,alt,vit;
  long long         time;
  struct gps_data_t *newdata;
  char              scr[128];
  if (!this->gps_rec->waiting(50000000)) return;

  if ((newdata = this->gps_rec->read()) == NULL) {
    cerr << "Read error.\n";
    return;
  } else {

    lat = newdata->fix.latitude;
    lon = newdata->fix.longitude;
    alt = newdata->fix.altitude;
    vit = newdata->fix.speed;

    (void)unix_to_iso8601(newdata->fix.time, scr, sizeof(scr));
    time = timecode(scr);

    if (lat != lat || lon != lon || alt != alt|| vit != vit) return;
    sql.str("");
    sql.clear();
    sql << setprecision(20) << "REPLACE INTO GpsBase (TIME,LAT,LON,ALT,VIT,errorLat,errorLon) VALUES (";
    sql << time << "," << lat << "," << lon << "," << alt << "," << vit << "," << lat - fixedLat << "," << lon - fixedLon << ")";
    this->db->Query(sql.str());
  }
  // clear old date, keep 1h
  long long Tmax = this->db->getBigInt("SELECT max(TIME) FROM GpsBase");
  sql.str("");
  sql.clear();
  sql << setprecision(20) << "DELETE FROM GpsBase WHERE TIME<" << minusOneHour(Tmax);
  this->db->Query(sql.str());
}

int main(int argc, char const *argv[]) {

  GpsBase myGPS;

  while (1) {
    if (myGPS.com->receiveNb()) {
      myGPS.parse();
    }
    myGPS.readGps();
    if (myGPS.quit) {
      break;
    }
  }
}
