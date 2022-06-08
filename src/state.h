
#ifndef C4LL_STATE_INC
#define C4LL_STATE_INC

#include "base_types.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

typedef struct State
{
  Bool running;
  SDL_Window* window;
  SDL_GLContext* context;
} State;

#endif
