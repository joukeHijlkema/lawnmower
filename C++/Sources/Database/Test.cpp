#include "mySql.hpp"
#include <iostream>
#include <vector>

long long minusOneHour(long long d) {
  std::cout << "old = " << d << std::endl;
  return d - 10000;

}

int main(int argc, char const *argv[]) {
  /* code */
  mySql     db;
  long long d = db.getBigInt("SELECT max(TIME) FROM GpsBase");
  std::cout << setprecision(20) << "received " << d << std::endl;

  std::cout << "new = " << minusOneHour(20160123002317) << "\n";
  std::cout << "new = " << minusOneHour(20160123012317) << "\n";
  std::cout << "new = " << minusOneHour(20160123112317) << "\n";

  return 0;
}
