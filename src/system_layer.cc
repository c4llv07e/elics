#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "system_layer.hh"

int
deinit_sdl(State* state)
{
  if (state->context == null)
    fputs("warning, context was already removed\n", stderr); 
  else
    SDL_GL_DeleteContext(state->context);
  if (state->window == null)
    fputs("warning, window was already removed\n", stderr);
  else
    SDL_DestroyWindow(state->window);

  SDL_Quit();
  return 0x0;
}

int
init_sdl(State* state)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0x0)
    {
      fputs("error, can't init sdl\n", stderr);
      return -0x1;
    }

  state->window = SDL_CreateWindow("test",
				   SDL_WINDOWPOS_UNDEFINED,
				   SDL_WINDOWPOS_UNDEFINED,
				   0x400,
				   0x200,
				   SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
  
  state->context = SDL_GL_CreateContext(state->window);
  
  return 0x0;
}

int
init_glew(State* state)
{
  if (state->context == null)
    {
      fputs("error, required inited sdl context to init glew\n", stderr);
      return -0x1;
    }
  SDL_GL_MakeCurrent(state->window, state->context);
  glewExperimental = 0x1;
  if (glewInit() != GLEW_OK)
    {
      fputs("error, can't init glew\n", stderr);
      return -0x1;
    }
  return 0x0;
}
