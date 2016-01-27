#include "mySpi.hpp"
#include <iostream>
#include <algorithm>

#include <unistd.h>

#ifdef rpi
#include <wiringPi.h>
#endif

/* ==============================================================
 * Description : mySpi class
 * initial version : 1.0
 * Author : hylkema (jouke.hijlkema@onera.fr)
 * date   :
 * ============================================================== */
mySpi::mySpi() {
#ifdef rpi
  wiringPiSetupPhys();
  pinMode (CSN, OUTPUT);
  pinMode (SCK, OUTPUT);
  pinMode (MOSI, OUTPUT);
  pinMode (MISO, INPUT);
  digitalWrite (CSN, HIGH);
  digitalWrite (SCK,HIGH);
#endif
}

mySpi::~mySpi() {
}
/**
 * prepare for transmission
 */
void mySpi::prepare() {
#ifdef rpi
  digitalWrite (CSN, LOW);
  usleep(1);
  digitalWrite (SCK,HIGH);
  usleep(1);
#else
  std::cout << "SPI prepare ..." << std::endl;
#endif
}
/**
 * end the transmission
 */
void mySpi::end() {
#ifdef rpi
  usleep(1);
  digitalWrite (CSN, HIGH);
  digitalWrite (SCK,HIGH);
#else
  std::cout << "SPI end ..." << std::endl;
#endif
}
/**
 * send a bitset over SPI, most significant bit first
 * @author Jouke Hijlkema
 * @date   2015-11-12T11:21:51+010
 * @param  in                      the bitset to send
 * @return                         the answer
 */
void mySpi::send(bitset<20> *out,bitset<20> *in) {
  cout << "send     : " << *out << endl;
  prepare();
  for (int i = out->size() - 1; i >= 0; i--) {
    in->set(i,sendBit(out->test(i)));
  }
  end();
  cout << "received : " << *in << endl;

}
/**
 * send a sendString
 * @param  out the string to send
 * @return     the answer
 */
string mySpi::sendString(string out) {
  string in;
  //remove spaces
  out.erase(std::remove(out.begin(), out.end(), ' '),out.end());
  std::cout << "send     : " << out << std::endl;
  prepare();
  for (auto c : out) {
    if (sendBit(c=='1')) {
      in.append("1");
    } else {
      in.append("0");
    }
  }
  std::cout << "received : " << in << std::endl;
  end();
  return in;
}
/**
 * send one bit
 * @param  bit the bit to send
 * @return     the answer
 */
bool mySpi::sendBit(bool bit) {
  bool out;
  int  hpw = pw / 2;
#ifdef rpi
  digitalWrite (SCK,LOW);
  usleep(hpw);
  digitalWrite (MOSI,bit);
  usleep(hpw);
  digitalWrite (SCK,HIGH);
  usleep(hpw);
  out = digitalRead (MISO);
  usleep(hpw);
  // std::cout << bit << " <-> " << out << std::endl;
#else
  std::cout << "SPI sendBit ..." << std::endl;
  out = 0;
#endif
  return out;
}
/**
 * send an unsigned long
 * @param  out to be send
 * @return     the answer
 */
unsigned long mySpi::sendLong(unsigned long out) {
  unsigned long x = static_cast<unsigned long>(out);
  // unsigned long long fix for issue pointed out by @Zac Howland in comments
  bitset<20> bout,bin;
  int        i = 0;

  while (x != 0 && i<20) {
    unsigned long bit = x & 1;
    if (bit==1) bout.set(19 - i,1);
    i++;
    x >>= 1;
  }
  this->send(&bout,&bin);
  return bin.to_ulong();
}
