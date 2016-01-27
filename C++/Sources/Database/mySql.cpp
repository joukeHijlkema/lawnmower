#include "mySql.hpp"
#include <iostream>

/* ==============================================================
 * Description : mySql class
 * initial version : 1.0
 * Author : hylkema (jouke.hijlkema@onera.fr)
 * date   :
 * ============================================================== */
mySql::mySql() {
  Db = new mysqlpp::Connection(false);
  if (Db->connected()) Db->disconnect();
  if (Db->connect("Grasmaaier","192.168.1.102","gpsBase","lekkerKort")) {
    cout << "Connected to 192.168.1.102 Database : Grasmaaier as User : gpsBase\n";
  } else {
    cout << "Connection failed :" << Db->error() << "\n";
  }
}

mySql::~mySql() {
}

/**
 * do a query
 * @author Jouke Hijlkema
 * @date   2016-01-16T14:32:06+010
 * @param  q                       [description]
 */
mysqlpp::Row mySql::Query(string q) {
  std::cout << "query : " << q << std::endl;
  mysqlpp::Row   out;
  mysqlpp::Query Q = Db->query();
  Q << q;
  if(mysqlpp::UseQueryResult res = Q.use()) {
    mysqlpp::Row r = res.fetch_row();
    if (r.empty()) {
      std::cout << "query gave empty result" << std::endl;
    } else {
      out = r;
    }
  } else {
    std::cout << "query gave no results" << std::endl;
  }
  return out;
}
/**
 * get one double out of the database
 * @author Jouke Hijlkema
 * @date   2016-01-16T15:29:57+010
 * @param  q                       [description]
 * @return                         [description]
 */
double mySql::getDouble(string q) {
  mysqlpp::Row res = this->Query(q);
  double       out = 0.0;
  if (res.size()==1) {
    std::cout << "res = " << res[0] << std::endl;
    out = double(res[0]);
  } else {
    std::cout << "wrong number of results !! return 0.0" << std::endl;
    out = 0.0;
  }
  return out;
}
/**
 * get some doubles out of the database
 * @param  q [description]
 * @return   [description]
 */
vector<double> mySql::getDoubles(string q) {
  vector <double> out;
  mysqlpp::Row    res = this->Query(q);
  for (auto d : res) {
    out.push_back(d);
  }
  return out;
}
/**
 * get some long doubles out of the database
 * @param  q [description]
 * @return   [description]
 */
vector<long double> mySql::getLongDoubles(string q) {
  vector <long double> out;
  mysqlpp::Row    res = this->Query(q);
  string tmp;
  for (auto d : res) {
    d.to_string(tmp);
    out.push_back(stold(tmp));
  }
  return out;
}
/**
 * get one int out of the database
 * @author Jouke Hijlkema
 * @date   2016-01-16T15:29:57+010
 * @param  q                       [description]
 * @return                         [description]
 */
int mySql::getInt(string q) {
  mysqlpp::Row res = this->Query(q);
  int          out = 0.0;
  if (res.size()==1) {
    std::cout << "res = " << res[0] << std::endl;
    out = int(res[0]);
  } else {
    std::cout << "wrong number of results !! return 0.0" << std::endl;
    out = 0.0;
  }
  return out;
}
/**
 * get one int out of the database
 * @author Jouke Hijlkema
 * @date   2016-01-16T15:29:57+010
 * @param  q                       [description]
 * @return                         [description]
 */
long long mySql::getBigInt(string q) {
  mysqlpp::Row res = this->Query(q);
  long long    out = 0.0;
  if (res.size()==1) {
    std::cout << "res = " << res[0] << std::endl;
    out = (long long)res[0];
  } else {
    std::cout << "wrong number of results !! return 0.0" << std::endl;
    out = 0.0;
  }
  return out;
}
