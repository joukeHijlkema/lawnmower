#include "mySpi.hpp"
#include <bitest>
int main(int argc, char const *argv[]) {
  mySpi SPI;

  bitset<20> In,Out;
  out = ("10010000000110110100");
  SPI.send(&Out,&In);
  // regs.push_back("11010000000000011111");
  // regs.push_back("11100000000000010000");
  // regs.push_back("00000000000000000000");
  // regs.push_back("10101000001000000010");

  // Out.set(2,1);
  // Out.set(4,1);
  // Out.set(5,1);
  // Out.set(7,1);
  // Out.set(8,1);
  // Out.set(17,1);
  // Out.set(19,1);

  return 0;
}
