CC = g++
CPP = $(CC)
COMMON_OBJS = main.o

ifdef SystemRoot
  RM = del /Q
  EXE = pilot.exe
#  LDFLAGS	=  
  DEFS  = 
  INCLUDES	= -I.
  LIBS = -lSDL
else
  ifeq ($(shell uname), Linux)
    RM = rm -f
    EXE = pilot
#    LDFLAGS	= -L/usr/local/lib
    DEFS = -DSTANDALONE -DHAVE_CONFIG_H -DHAVE_GTK2
    INCLUDES = -I.
    LIBS = -lSDL
    OBJS = $(COMMON_OBJS)
  endif
endif

CFLAGS += -std=c++0x -Wall -Weffc++ -pedantic -U__STRICT_ANSI__

#HEADERS = $(wildcard *.hpp)

default: all

all: pilot

pilot: $(COMMON_OBJS)
	$(CPP) -o pilot *.o $(LIBS)

main.o: main.cpp
	$(CPP) -c -o main.o $(CFLAGS) main.cpp

clean:
	$(RM) *.o $(EXE) core

