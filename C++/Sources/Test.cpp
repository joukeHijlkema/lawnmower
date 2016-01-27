#include "Tools.hpp"
#include <iostream>
int main(int argc, char const *argv[]) {
  std::cout << "timecode = " << timecode("2016-01-18T21:49:17.000Z")<<"\n";
  return 0;
}
