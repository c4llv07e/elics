
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

typedef void (*exit_f)(void);

exit_f* exits;
int exits_len = 0x0;

void
my_exit(int val)
{
  for (int i = exits_len-1; i >= 0; --i)
    exits[i]();
  exit(val);
  return;
}

extern int init_exit(void);
extern void free_exit(void);
extern int add_exit(exit_f ex);

int
init_exit(void)
{
  if ((exits = (exit_f*) malloc(sizeof(exit_f))) == NULL)
    exit(-0x1);
  return add_exit(free_exit);
}

void
free_exit(void)
{
  free(exits);
}

int
add_exit(exit_f ex)
{
  if ((exits = realloc(exits, sizeof(exit_f)*(0x1+exits_len))) == NULL)
    exit(-0x1);
  exits[exits_len++] = ex;
  return 0x0;
}

int running = 0x1;

int
main(void)
{
  init_exit();
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0x0)
    {
      fputs("error, can't init sdl\n", stderr);
      my_exit(-0x1);
    }
  add_exit(SDL_Quit);

  SDL_Window* window;
  SDL_Renderer* renderer;

  window = SDL_CreateWindow("test",
			    SDL_WINDOWPOS_UNDEFINED,
			    SDL_WINDOWPOS_UNDEFINED,
			    0x400,
			    0x200,
			    SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

  renderer = SDL_CreateRenderer(window, -0x1, SDL_RENDERER_ACCELERATED);
			    

  while (running)
    {
      SDL_Event event;
      while(SDL_PollEvent(&event))
	{
	  switch (event.type)
	    {
	    case SDL_QUIT:
	      running = 0x0;
	      break;
	    }
	}
      SDL_RenderClear(renderer);
      SDL_RenderPresent(renderer);
    }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  my_exit(0x0);
}
