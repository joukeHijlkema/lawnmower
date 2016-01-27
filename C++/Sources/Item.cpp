#include "Item.hpp"
#include <utility>

/* ==============================================================
 * Description : Item class
 * initial version : 1.0
 * Author : hylkema (jouke.hijlkema@onera.fr)
 * date   :
 * ============================================================== */
Item::Item() {
}

Item::~Item() {
  this->quit = false;
  }
/**
 * parse the messages
 * @author Jouke Hijlkema
 * @date   2015-10-13T15:36:41+020
 */
void Item::parse() {
  if (this->com->got("Global","Quit")||this->com->got(this->com->getName(),"Quit")) {
    this->quit = true;
  }
  if (this->com->got("Global","Alive?")) {
    this->com->send(this->com->getName()+":Alive");
  }
}
