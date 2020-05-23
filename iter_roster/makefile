SYS := $(shell gcc -dumpmachine)
ifneq (,$(findstring linux, $(SYS)))
# Flags for Linux
CPPFLAGS=-g -std=c++14 $(MMD) -fsanitize=address -D_GLIBCXX_DEBUG -Wall
LFLAGS=-fuse-ld=gold -pthread
RM=/bin/rm -rf
EXE=
else ifneq (,$(findstring apple, $(SYS)))
# Flags for macOs
CPPFLAGS=-g -std=c++14 $(MMD) -fsanitize=address -D_GLIBCXX_DEBUG -Wall
LFLAGS=
RM=/bin/rm -rf
EXE=
else ifneq (,$(findstring cygwin, $(SYS)))
# Flags for CygWin
CPPFLAGS=-g -std=c++14 $(MMD) -D_GLIBCXX_DEBUG -Wall
LFLAGS=
RM=del /q
EXE=.exe
else ifneq (,$(findstring mingw, $(SYS)))
# Flags for MinGW
CPPFLAGS=-g -std=c++14 $(MMD) -D_GLIBCXX_DEBUG -Wall
LFLAGS=
RM=del /q
EXE=.exe
else
# Who knows what the heck this is?
CPPFLAGS=-g -std=c++14 $(MMD) -D_GLIBCXX_DEBUG -Wall
LFLAGS=
RM=echo
EXE=.exe
endif
#
####################################################
# Customization for this project
#
TARGET=listrosters$(EXE)
CPPS=$(wildcard *.cpp)
HEADERS=$(wildcard *.h)
OBJS=listrosters.o faculty.o io_ops.o section.o course.o student.o name.o
TESTOBJS=faculty.o io_ops.o section.o course.o student.o name.o testFaculty.o unittest.o
#

#
########################################################################
# Macro definitions for "standard" C and C++ compilations
#
#
CC=gcc
CXX=g++
CFLAGS=-g
LINK=g++ $(CPPFLAGS)
#
#
#
#  In most cases, you should not change anything below this line.
#
#  The following is "boilerplate" to set up the standard compilation
#  commands:
#


%.d: %.cpp
	touch $@

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -o $@ -c $*.cpp

#
# Targets:
#

all: $(TARGET) runtests$(EXE)

$(TARGET): $(OBJS)
	$(LINK) $(FLAGS) -o $@ $^ $(LFLAGS)

runtests$(EXE): $(TESTOBJS)
	$(LINK) $(FLAGS) -o $@ $^ $(LFLAGS)


# Convenience target for use with Code::Blocks
Debug: all

docs: documentation

clean:
	-$(RM) *.o $(TARGET) runtests$(EXE) docs

cleanDebug: clean

documentation:
	-mkdir docs
	doxygen Doxyfile

make.dep: $(HEADERS) $(CPPS)
	-make all MMD=-MMD
	-cat *.d > $@
	-rm *.d

##include make.dep
course.o: course.cpp course.h
faculty.o: faculty.cpp faculty.h name.h section.h course.h student.h
io_ops.o: io_ops.cpp course.h faculty.h name.h section.h student.h
listrosters.o: listrosters.cpp section.h course.h student.h name.h \
 faculty.h
name.o: name.cpp name.h
section.o: section.cpp section.h course.h student.h name.h
student.o: student.cpp student.h name.h
testFaculty.o: testFaculty.cpp faculty.h name.h section.h course.h \
 student.h unittest.h
unittest.o: unittest.cpp unittest.h

