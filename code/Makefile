CC = g++
CPP = $(CC) -pedantic -Wall -U__STRICT_ANSI__
COMMON_OBJS = wiz.o implementation.o utility.o flyerz.o

INCLUDES = -I../include/
OBJS = $(COMMON_OBJS)
LDFLAGS =
DEFS = -DSTANDALONE -DHAVE_CONFIG_H -DHAVE_GTK2
HEADERS = $(wildcard $(INCLUDES)*.hpp)

default: all

all: wiz

wiz: $(OBJS)
	$(CPP_HACK) -o $@ $(OBJS) $(HACK_LIBS) $(CFLAGS)

wiz.o: wiz.cpp wiz.hpp flyerz.hpp drawinterface.hpp
	$(CPP) -c $(INCLUDES) $(DEFS) $(CFLAGS)  $<

flyerz.o: flyerz.cpp wiz.hpp flyerz.hpp drawinterface.hpp
	$(CPP) -c $(INCLUDES) $(DEFS) $(CFLAGS)  $<

implementation.o: implementation.cpp wiz.hpp drawinterface.hpp implementation_gdi.cpp implementation_xlib.cpp
	$(CPP) -c $(INCLUDES) $(DEFS) $(CFLAGS)  $<

utility.o: utility.cpp drawinterface.hpp flyerz.hpp
	$(CPP) -c $(INCLUDES) $(DEFS) $(CFLAGS)  $<

%o: %cpp

clean:
	$(RM) *.o $(EXE) core


