
#ifndef C4LL_PROGRAM_INC
#define C4LL_PROGRAM_INC

#include <GL/glew.h>
#include <GL/gl.h>

#include "base_types.hh"

typedef struct Program
{
  GLuint frag;
  GLuint vert;
  GLuint program;
} Program;

Program* create_program(void* (*alloc)(size_t));
int program_load_default_shaders(Program* program);
int program_link(Program* program);
int use_program(Program* program);
int delete_program(Program* program);

#endif
