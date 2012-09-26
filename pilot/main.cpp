#include "SDL/SDL.h"

int main(int argc, char* argv[])
{
  SDL_Init( SDL_INIT_EVERYTHING );

  SDL_Surface* screen(SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE));
  SDL_Surface* pic(SDL_LoadBMP(argv[1]));

  SDL_BlitSurface(pic, 0, screen, 0);
  SDL_Flip(screen);

  SDL_Delay( 2000 );

  SDL_FreeSurface( pic );

  SDL_Quit();
}
