#include "mySpi.hpp"
#include <wirinngPi.hpp>

#include <unistd.h>

/* ==============================================================
 * Description : mySpi class
 * initial version : 1.0
 * Author : hylkema (jouke.hijlkema@onera.fr)
 * date   :
 * ============================================================== */
mySpi::mySpi() {
  wiringPiSetupPhys();
  pinMode (CSN, OUTPUT);
  pinMode (SCK, OUTPUT);
  pinMode (SDO, OUTPUT);
  pinMode (SDI, INPUT);
}

mySpi::~mySpi() {
}

/**
 * send a bitset over SPI, most significant bit first
 * @author Jouke Hijlkema
 * @date   2015-11-12T11:21:51+010
 * @param  in                      the bitset to send
 * @return                         the answer
 */
void mySpi::send(bitset<20> *out,bitset<20> *in) {

  std::cout << "send : " << *out << std::endl;
  digitalWrite (CSN, LOW);
  usleep(1);
  digitalWrite (SCK,HIGH);
  usleep(1);
  for (int i = out->size[] - 1; i >= 0; i--) {
    digitalWrite (SCK,LOW);
    usleep(1);

    digitalWrite (SDO,out->test(i));
    in->set(i,digitalRead (SDI));

    digitalWrite (SCK,HIGH);
    usleep(1);
  }
  usleep(1);
  digitalWrite (CSN, HIGH);
  std::cout << "received : "<< *in << std::endl;

}
