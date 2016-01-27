#include "ipinfo.hpp"
#include <stdio.h>

/* ==============================================================
 * Description : ipinfo class
 * initial version : 1.0
 * Author : hylkema (jouke.hijlkema@onera.fr)
 * date   :
 * ============================================================== */
ipinfo::ipinfo() {
  FILE *lsofFile_p = popen("ip -4 -o addr show dev eth0 |awk '{split($4,a,\"/\") ;print a[1]}'", "r");
  char buffer[1024];
  this->ip = fgets(buffer, sizeof(buffer), lsofFile_p);
  pclose(lsofFile_p);
  this->ip.erase(this->ip.find_last_not_of(" \n\r\t")+1);
}

ipinfo::~ipinfo() {
}
