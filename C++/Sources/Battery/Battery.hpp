#ifndef Battery_JOUKE
#define Battery_JOUKE

#include "Item.hpp"
#include <string>

using namespace std;

/*! -------------------------------------------------------------
 * brief   Battery class
 * details
 * author  Jouke Hijlkema (jouke.hijlkema@onera.fr)
 * date    Date
 * version 1.0
 *
 * -------------------------------------------------------------*/
class Battery:public Item {
public:

  Battery();
  ~Battery();

  string Status();

  void parse();

protected:

private:
  int High=3;
  int Medium=5;
  int Low=7;


};
#endif
