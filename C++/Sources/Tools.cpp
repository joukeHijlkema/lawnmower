#include "Tools.hpp"
#include <iostream>

string token(string s,int loc,bool rest) {
  size_t pos = 0;
  string token;
  while ((pos = s.find(delimiter)) != string::npos) {
    loc  += -1;
    token = s.substr(0, pos);
    if (loc==0) {
      if (rest) return s;
      return token;
    }
    s.erase(0, pos + delimiter.length());
  }
  return s;
}
long long timecode(string s) {
  // 0123456789012345678
  // 2016-01-18T21:49:17.000Z
  string tmp;
  long long  out = 0;
  std::string::size_type sz;
  out = 10000000000 * stoi(s.substr(0,4));
  out += 100000000 * stoi(s.substr(5,2));
  out += 1000000 * stoi(s.substr(8,2));
  out += 10000 * stoi(s.substr(11,2));
  out += 100 * stoi(s.substr(14,2));
  out += stoi(s.substr(17,2));
  return out;
}

long long minusOneHour(long long d) {
  long long date    = d/1000000;
  long long hours   = d/10000-100*date;
  long long minutes = d-hours*10000-date*1000000;

  std::cout << "/* date    */" << date << std::endl;
  std::cout << "/* hour    */" << hours << std::endl;
  std::cout << "/* minutes */" << minutes << std::endl;

  if (hours>0) hours+=-1;

  long long out = date*1000000+hours*10000+minutes;

  return out;
}
