CPP = g++

libraries = -lmysqlpp -lmysqlclient -Wl,--no-as-needed

# Path and names
main_path      = $(PWD)
obj            = $(main_path)/obj
src            = $(main_path)
exe            = $(main_path)

common_buildflags_CC =
buildflags_CC_$(MACHTYPE) = -Wall -I. -O2 -std=c++11 -g
buildflags_CC =$(buildflags_CC_$(MACHTYPE)) $(common_buildflags_CC) $(defines)

includes = -I. -I/usr/include/mysql++ -I/usr/include/mysql

VPATH = $(obj)

objects = mySql.o Test.o
executable = Test.exe

default: depend objdir all

objdir:
	cd $(exe); mkdir  -p $(obj); touch make.dep

source = $(wildcard ./*.cpp)

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
