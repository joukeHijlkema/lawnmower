#include "GpsBase.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

/* ==============================================================
 * Description : GpsBase class
 * initial version : 1.0
 * Author : hylkema (jouke.hijlkema@onera.fr)
 * date   :
 * ============================================================== */
GpsBase::GpsBase() {
  this->com = new zmqClient("GpsBase","GpsBase",PILOT_IN,PILOT_OUT,SUB_PUSH);
  this->db  = new Database("/home/pi/gpsBase.db");

  this->gps_rec =  new gpsmm("localhost", DEFAULT_GPSD_PORT);
  if (gps_rec->stream(WATCH_ENABLE | WATCH_JSON) == NULL) {
    cerr << "No GPSD running.\n";
    exit(1);
  }
  this->com->send("GpsBase:Online");
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

  if (this->com->got("GpsBase","Update")) this->sendUpdate();

}
/**
 * send an update to the pilot
 * @author Jouke Hijlkema
 * @date   2016-01-03T16:28:56+010
 */
void GpsBase::sendUpdate() {
  std::cout << "start update" << std::endl;
  ostringstream out;
  out << setprecision(20) << "GpsBase:Update:LAT:";
  out << this->db->getDouble("SELECT avg(LAT) FROM MESURES",0) << ":";
  out << this->db->getDouble("SELECT min(LAT) FROM MESURES",0) << ":";
  out << this->db->getDouble("SELECT max(LAT) FROM MESURES",0) << ":";
  out << this->db->getStdev("LAT") << ":";
  out << "LON:";
  out << this->db->getDouble("SELECT avg(LON) FROM MESURES",0) << ":";
  out << this->db->getDouble("SELECT min(LON) FROM MESURES",0) << ":";
  out << this->db->getDouble("SELECT max(LON) FROM MESURES",0) << ":";
  out << this->db->getStdev("LON") << ":";
  out << "ALT:";
  out << this->db->getDouble("SELECT avg(ALT) FROM MESURES",0) << ":";
  out << this->db->getDouble("SELECT min(ALT) FROM MESURES",0) << ":";
  out << this->db->getDouble("SELECT max(ALT) FROM MESURES",0) << ":";
  out << this->db->getStdev("ALT") << ":";
  out << this->db->getDouble("SELECT max(TIME)-min(TIME) FROM MESURES",0);
  this->com->send(out.str());
  std::cout << "end update" << std::endl;
}
/**
 * read the GPS data
 * @author Jouke Hijlkema
 * @date   2016-01-02T23:52:31+010
 */
void GpsBase::readGps() {
  ostringstream     sql;
  double            lat,lon,alt,time;
  struct gps_data_t *newdata;
  if (!this->gps_rec->waiting(50000000)) return;

  if ((newdata = this->gps_rec->read()) == NULL) {
    cerr << "Read error.\n";
    return;
  } else {
    lat  = newdata->fix.latitude;
    lon  = newdata->fix.longitude;
    alt  = newdata->fix.altitude;
    time = newdata->fix.time;
    if (lat != lat || lon != lon || alt != alt) return;
    sql.str("");
    sql.clear();
    sql << setprecision(20) << "INSERT OR REPLACE INTO MESURES (TIME,LAT,LON,ALT) VALUES (";
    sql << time << "," << lat << "," << lon << "," << alt << ")";
    this->db->Query(sql.str());
  }
  // clear old date, keep 24h
  double Tmax = this->db->getDouble("SELECT max(TIME) FROM MESURES",0);
  sql.str("");
  sql.clear();
  sql << "DELETE FROM MESURES WHERE TIME<" << Tmax - 86400;
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
