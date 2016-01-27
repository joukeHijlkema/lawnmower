# usage make BUILD=target

host-type := $(shell arch)
host-name := $(shell hostname)
libraries = -lpthread -lzmqpp -lzmq -lsodium -lmysqlpp -lmysqlclient -Wl,--no-as-needed
ifeq "$(host-type)" "armv6l"
ifeq "$(host-name)" "gpsBase"
defines = -Drpi2
else
defines = -Drpi
endif
CPP = g++-4.7
libraries += -lQgpsmm -lwiringPi
else ifeq "$(host-type)" "i686"
CPP = g++
defines = -DpcHome
else
CPP = g++
defines = -DpcWork
endif

# Path and names
main_path      = $(PWD)
obj            = $(main_path)/obj_$(host-type)
src            = $(main_path)
exe            = $(main_path)

common_buildflags_CC =
buildflags_CC_$(MACHTYPE) = -Wall -I. -O2 -std=c++11 -g
buildflags_CC =$(buildflags_CC_$(MACHTYPE)) $(common_buildflags_CC) $(defines)

includes = -I.\
 -I./Sources\
 -I./Sources/Database\
 -I./Sources/gpsBase\
 -I./Sources/ZMQ\
 -I./Sources/gpsMaaier\
 -I/./Sources/Battery\
 -I/usr/include/mysql++ -I/usr/include/mysql

VPATH = $(obj)\
	./Sources\
	./Sources/Database\
	./Sources/gpsBase\
	./Sources/gpsMaaier\
	./Sources/ZMQ\
	./Sources/Battery

ifeq "$(BUILD)" "testPub"
objects = testPub.o
executable = testPub.exe
else ifeq "$(BUILD)" "testSub"
objects = testSub.o
executable = testSub.exe
else ifeq "$(BUILD)" "shutdownClient"
objects = zmqClient.o shutdownClient.o ipinfo.o Tools.o Item.o
executable = shutdownClient.exe
else ifeq "$(BUILD)" "batteryMonitor"
objects = zmqClient.o batteryMonitor.o Tools.o Item.o
executable = batteryMonitor.exe
else ifeq "$(BUILD)" "shutdown"
objects = shutdown.o
executable = shutdown.exe
else ifeq "$(BUILD)" "grasmaaier"
objects = zmqClient.o grasmaaier.o Tools.o Item.o
executable = grasmaaier.exe
else ifeq "$(BUILD)" "gpsMaaier"
objects = zmqClient.o gpsMaaier.o mySql.o Tools.o Item.o
executable = gpsMaaier.exe
else ifeq "$(BUILD)" "blades"
objects = zmqClient.o Blades.o Tools.o Item.o
executable = Blades.exe
else ifeq "$(BUILD)" "motor"
objects = zmqClient.o Motor.o GPIO.o Tools.o Item.o
executable = Motor.exe
else ifeq "$(BUILD)" "battery"
objects = zmqClient.o Battery.o Tools.o Item.o
executable = Battery.exe
else ifeq "$(BUILD)" "direction"
objects = zmqClient.o Tools.o mySpi.o Direction.o Item.o
executable = Direction.exe
else ifeq "$(BUILD)" "gpsBase"
objects = mySql.o GpsBase.o Item.o zmqClient.o Tools.o
executable = GpsBase.exe
else ifeq "$(BUILD)" "zmqTest"
objects = zmqTest.o Item.o zmqClient.o Tools.o
executable = zmqTest.exe
endif

default: depend objdir all

objdir:
	cd $(exe); mkdir  -p $(obj); touch make.dep

source = $(wildcard Sources/*.cpp)

.SUFFIXES: .c .cpp

# Now create exe

# dependencies
-include make.dep

# Rules for c++ source code
.cpp.o:
	@echo
	@echo "###################### "
	@echo "# Compiling $(@F) "
	@echo "  compiler : $(CPP)"
	@echo "  flags    : $(buildflags_CC)"
	@echo "  includes : ${includes}"
	@echo "# Messages "
	@${CPP} ${includes} -c ${buildflags_CC} $< -o $(obj)/$@
	@echo "###################### "


all	: $(objects)
	-mkdir -p  $(obj)
	@echo objects = $(objects)
	@echo ---------------------------------------------------------------
	@echo Machine is $(host-type)
	@echo Linking object files for $(executable)
	@echo $(CPP) $(linkflags) -o $(executable) $^ '[object files]' $(libraries)
	@cd $(obj) ; $(CPP) $(linkflags) -o ../$(executable) $^ $(libraries)



clean  :
	@rm -f $(obj)/*.o
	@rm -f $(wildcard *.exe)

# Rule for dependencies
%.cpp:
depend : $(source)
	@rm -f make.dep
	@touch make.dep
	@echo "##################### "
	@echo "# Find dependencies # "
	@echo "##################### "
	@echo "# Messages "
	@$(CPP) -MM ${buildflags_CC} $(includes) $^ >> make.dep
	@echo "###################### "
