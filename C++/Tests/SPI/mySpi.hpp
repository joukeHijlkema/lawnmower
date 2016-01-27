#ifndef mySpi_JOUKE
#define mySpi_JOUKE

#include <bitset>

using namespace std;

/*! -------------------------------------------------------------
 * brief   mySpi class
 * details
 * author  Jouke Hijlkema (jouke.hijlkema@onera.fr)
 * date    Date
 * version 1.0
 *
 * -------------------------------------------------------------*/
class mySpi {
public:

  mySpi();
  ~mySpi();
  void send(bitset<20> *in,bitset<20> *out);

protected:

private:
  int CSN = 24;
  int SCK = 23;
  int SDI = 19;
  int SDO = 21;
};
#endif
