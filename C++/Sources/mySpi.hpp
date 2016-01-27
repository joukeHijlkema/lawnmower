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
  void   send(bitset<20> *in,bitset<20> *out);
  string sendString(string out);
  bool   sendBit(bool bit);
  unsigned long sendLong(unsigned long out);

protected:
  void prepare();
  void end();

private:
  static const int CSN  = 24;
  static const int SCK  = 23;
  static const int MOSI = 19;
  static const int MISO = 21;
  static const int pw   = 20; // pulswith in microseconds
};
#endif
