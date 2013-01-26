CC = g++
CPP = $(CC)

GRAPHICS_OBJS = main.o drawfunctions.o graphics.o basic_elements.o physics.o flyer.o accessory/rocket_engine.o

ifdef SystemRoot
  RM = del /Q /S
  EXE = *.exe
  DEFS  =
  INCLUDES	= -I. -I$(SDL_HOME)/include
  LIBPATH = -L$(SDL_HOME)/lib
  LIBS = -lmingw32 -lSDLmain -lSDL -lBox2D
else
  ifeq ($(shell uname), Linux)
    RM = rm -rf
    EXE = physics graphics
    DEFS = -DSTANDALONE -DHAVE_CONFIG_H -DHAVE_GTK2
    INCLUDES = -I.
    LIBS = -lSDL -lBox2D
  endif
endif

CFLAGS += -std=c++0x -Wall -Weffc++ -pedantic -U__STRICT_ANSI__

default: graphics

all: graphics

graphics: $(GRAPHICS_OBJS)
	$(CPP) -o graphics $(GRAPHICS_OBJS) $(LIBS) $(LIBPATH)

%.o: %.cpp
	$(CPP) -c -o $@ $(CFLAGS) $(INCLUDES) $<

clean:
	$(RM) *.o $(EXE) core

