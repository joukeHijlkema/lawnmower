#ifndef adresses_JOUKE
#define adresses_JOUKE

#ifdef rpi
static const std::string LOCAL_OUT = "tcp://192.168.1.11:4242";
static const std::string LOCAL_IN  = "tcp://192.168.1.11:4243";
static const std::string PILOT_OUT = "tcp://192.168.1.102:4244";
static const std::string PILOT_IN  = "tcp://192.168.1.102:4245";
#endif
#ifdef rpi2
static const std::string LOCAL_OUT = "tcp://192.168.1.12:4242";
static const std::string LOCAL_IN  = "tcp://192.168.1.12:4243";
static const std::string PILOT_OUT = "tcp://192.168.1.102:4244";
static const std::string PILOT_IN  = "tcp://192.168.1.102:4245";
#endif
#ifdef pcWork
static const std::string LOCAL_OUT = "tcp://127.0.0.1:4242";
static const std::string LOCAL_IN  = "tcp://127.0.0.1:4243";
static const std::string PILOT_OUT = "tcp://127.0.0.1:4244";
static const std::string PILOT_IN  = "tcp://127.0.0.1:4245";
#endif
#ifdef pcHome
static const std::string LOCAL_OUT = "tcp://192.168.1.102:4242";
static const std::string LOCAL_IN  = "tcp://192.168.1.102:4243";
static const std::string PILOT_OUT = "tcp://192.168.1.102:4244";
static const std::string PILOT_IN  = "tcp://192.168.1.102:4245";
#endif

#endif
