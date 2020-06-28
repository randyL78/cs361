DIR=${PWD}
ASST=$(notdir ${DIR})
MAINPROG=animal
CC=gcc
CXX=g++
##
# Adjust settings for differnt compilers
#
UsingMinGW=$(shell $(CXX) -v 2>&1 | grep "^Target: mingw" | wc -l)
ifeq ($(UsingMinGW), 1)
CPPFLAGS=-g -std=c++11
LFLAGS=
else
CPPFLAGS=-g -std=c++14
LFLAGS=-pthread
endif
#
########################################################################
# Macro definitions for "standard" C and C++ compilations
#
CFLAGS=-g
TARGET=$(MAINPROG)
CPPS=animal.cpp node.cpp
LINK=g++ $(CPPFLAGS)
#
#
#  In most cases, you should not change anything below this line.
#
#  The following is "boilerplate" to set up the standard compilation
#  commands:
#


OBJS=$(CPPS:%.cpp=%.o)
DEPENDENCIES = $(CPPS:%.cpp=%.d)



%.d: %.cpp
	touch $@

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -MMD -o $@ -c $*.cpp

# 
# Targets:
# 
all: $(TARGET)

$(TARGET): $(OBJS)
	$(LINK) $(FLAGS) -o $(TARGET) $(OBJS) $(LFLAGS)

unittest: testTreeIO.o node.o unittest.o
	$(LINK) $(FLAGS) -o $@ $^ $(LFLAGS)

clean:
	-/bin/rm -f *.d *.o $(TARGET) unittest



make.dep: $(DEPENDENCIES)
	-cat $(DEPENDENCIES) > $@

include make.dep
