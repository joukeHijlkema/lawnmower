#ifndef Database_JOUKE
#define Database_JOUKE

#include <sqlite3.h>
#include <string>
#include <vector>
using namespace std;

/*! -------------------------------------------------------------
* brief   Database class
* details
* author  Jouke Hijlkema (jouke.hijlkema@onera.fr)
* date    Date
* version 1.0
*
* -------------------------------------------------------------*/
class Database {
public:

  Database(string file);
  ~Database();
  sqlite3_stmt* Query(string sql);
  double getDouble(string sql, int iCol);
  vector<double> getDoubles(string sql);
  vector<long double> getLongDoubles(string sql);
  double getStdev(string col);

protected:

private:

  sqlite3 *db;

};
#endif
