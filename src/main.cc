
#define DEBUG

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "base_types.hh"
#include "state.hh"
#include "system_layer/system_layer.hh"

State*
create_state(void* (*alloc)(size_t))
{
  State* state;

  state = (State*) alloc(sizeof(State));
  if (state == null)
    {
      fputs("error, can't allocate state\n", stderr);
      return null;
    }
  memset(state, 0x0, sizeof(State));
  
  return state;
}

int
state_run(State* state)
{
  state->running = True;
  return 0x0;
}

int
handle_events(State* state)
{
  SDL_Event event;
  while(SDL_PollEvent(&event))
    {
      switch (event.type)
	{
	case SDL_QUIT:
	  state->running = 0x0;
	  break;
	}
    }
  return 0x0;
}

int
render_present(State* state)
{
  SDL_GL_SwapWindow(state->window);
  glClearColor(0.3f, 0.7f, 0.8f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  return 0x0;
}

int
render_elements(State* state)
{
  /* TODO */
  return 0x0;
}

int
game_render(State* state)
{
  render_elements(state);
  render_present(state);
  return 0x0;
}

int
init_elements(State* state)
{
  
  return 0x0;
}

int
game_render_init(State* state)
{
  init_elements(state);
  return 0x0;
}

int
game_main(State* state)
{
  game_render_init(state);
  while (state->running)
    {
      handle_events(state);
      game_render(state);
    }
  return 0x0;
}

int
main(void)
{
  State* state;

  state = create_state(malloc);

  init_sdl(state);

  init_glew(state);

  state_run(state);

  game_main(state);

  deinit_sdl(state);
  
  return 0x0;
}
