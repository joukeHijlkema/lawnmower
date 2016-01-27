#ifndef mySql_JOUKE
#define mySql_JOUKE

#include <mysql++.h>

#include <string>
#include <vector>

using namespace std;

/*! -------------------------------------------------------------
* brief   mySql class
* details
* author  Jouke Hijlkema (jouke.hijlkema@onera.fr)
* date    Date
* version 1.0
*
* -------------------------------------------------------------*/
class mySql {
public:

  mySql();
  ~mySql();

  mysqlpp::Row        Query(string q);
  double              getDouble(string q);
  vector<double>      getDoubles(string q);
  vector<long double> getLongDoubles(string q);
  int                 getInt(string q);
  long long           getBigInt(string q);

protected:

private:
  mysqlpp::Connection *Db;
};
#endif
