CC = g++
CPP = $(CC)

GRAPHICS_OBJS = main.o drawfunctions.o graphics.o basic_elements.o physics.o flyer.o accessory/rocket_engine.o framework.o

COMMON_LIBS = -lSDL -lBox2D

ifdef SystemRoot
  RM = del /Q /S
  EXE = graphics.exe
  DEFS  =
  INCLUDES	= -I. -I$(SDL_HOME)/include
  LIBPATH = -L$(SDL_HOME)/lib
  LIBS = -lmingw32 -lSDLmain $(COMMON_LIBS)
else
  RM = rm -rf
  EXE = graphics
  DEFS = -DSTANDALONE -DHAVE_CONFIG_H -DHAVE_GTK2
  INCLUDES = -I. -I$(SDL_HOME)/include
  LIBPATH = -L$(SDL_HOME)/lib
  LIBS = $(COMMON_LIBS)
endif

CFLAGS += -std=c++0x -Wall -Weffc++ -pedantic -U__STRICT_ANSI__ -g 

default: graphics

all: graphics

graphics: $(GRAPHICS_OBJS)
	$(CPP) -g -o graphics $(GRAPHICS_OBJS) $(LIBS) $(LIBPATH)

%.o: %.cpp
	$(CPP) -c -o $@ $(CFLAGS) $(INCLUDES) $<

clean:
	$(RM) *.o $(EXE) core

