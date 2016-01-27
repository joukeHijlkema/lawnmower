#include "Database.hpp"

#include <iostream>
#include <sstream>

/* ==============================================================
 * Description : Database class
 * initial version : 1.0
 * Author : hylkema (jouke.hijlkema@onera.fr)
 * date   :
 * ============================================================== */
Database::Database(string file) {
  int rc = sqlite3_open(file.c_str(), &this->db);
  if(rc) {
    cout << "Can't open database:" << sqlite3_errmsg(this->db) << "\n";
    exit(0);
  }else{
    cout << "Opened database successfully \n";
  }
}

Database::~Database() {
}

/**
 * prepare and step a query
 * @author Jouke Hijlkema
 * @date   2016-01-03T13:02:00+010
 * @param  sql                     query
 * @return                         sqlite statement
 */
sqlite3_stmt* Database::Query(string sql) {
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(this->db,sql.c_str(),-1,&stmt,NULL);
  if (rc != SQLITE_OK) cout << "db error : " << sqlite3_errmsg(db) << "\n";

  rc = sqlite3_step(stmt);
  if (rc != SQLITE_ROW && rc != SQLITE_DONE) {
    cout << "db error : " << sqlite3_errmsg(db) << "\n";
    sqlite3_finalize(stmt);
  }
  if (rc == SQLITE_DONE) {
    sqlite3_finalize(stmt);
    // cout << sql << " : no results\n";
  }
  return stmt;
}
/**
 * get a double from the database
 * @author Jouke Hijlkema
 * @date   2016-01-03T13:31:48+010
 * @param  sql                     query
 * @return                         results
 */
double Database::getDouble(string sql, int iCol) {
  return sqlite3_column_double(this->Query(sql), iCol);
}
vector<double> Database::getDoubles(string sql) {
  vector <double> out;
  sqlite3_stmt *stmt =this->Query(sql);
  for (int i = 0; i < sqlite3_data_count(stmt); i++) {
    out.push_back(sqlite3_column_double(this->Query(sql), i));
  }
  return out;
}
vector<long double> Database::getLongDoubles(string sql) {
  vector <long double> out;
  sqlite3_stmt *stmt =this->Query(sql);
  for (int i = 0; i < sqlite3_data_count(stmt); i++) {
    out.push_back(sqlite3_column_double(this->Query(sql), i));
  }
  return out;
}

/**
 * get the standard deviation of col
 * src : http://stackoverflow.com/questions/2298339/standard-deviation-for-sqlite
 * @author Jouke Hijlkema
 * @date   2016-01-03T20:26:43+010
 * @param  col                     [description]
 * @return                         [description]
 */
double Database::getStdev(string col) {
  ostringstream     sql;
  sql << "SELECT AVG((MESURES.";
  sql << col;
  sql << " - sub.a) * (MESURES.";
  sql << col;
  sql << " - sub.a)) as var from MESURES,(SELECT AVG(";
  sql << col;
  sql << ") AS a FROM MESURES) AS sub;";
  return this->getDouble(sql.str(),0);
}
