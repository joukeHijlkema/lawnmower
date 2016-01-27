#ifndef Tools_JOUKE
#define Tools_JOUKE

#include <string>

using namespace std;

static const string delimiter=":";

string token(string s,int loc,bool rest);
long long timecode(string s);
long long minusOneHour(long long d);

#endif
