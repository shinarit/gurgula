CC = g++
CPP = $(CC)
COMMON_OBJS = main.o

ifdef SystemRoot
  RM = del /Q
  EXE = pilot.exe
  DEFS  =
  INCLUDES	= -I. -I$(SDL_HOME)/include
  LIBPATH = -L$(SDL_HOME)/lib
  LIBS = -lmingw32 -lSDLmain -lSDL
else
  ifeq ($(shell uname), Linux)
    RM = rm -f
    EXE = pilot
    DEFS = -DSTANDALONE -DHAVE_CONFIG_H -DHAVE_GTK2
    INCLUDES = -I.
    LIBS = -lSDL
  endif
endif

CFLAGS += -std=c++0x -Wall -Weffc++ -pedantic -U__STRICT_ANSI__

default: all

all: pilot

pilot: $(COMMON_OBJS)
	$(CPP) -o pilot *.o $(LIBS) $(LIBPATH)

main.o: main.cpp
	$(CPP) -c -o main.o $(CFLAGS) $(INCLUDES) main.cpp

clean:
	$(RM) *.o $(EXE) core

