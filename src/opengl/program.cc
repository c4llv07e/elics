
#include "program.hh"

#include <stdio.h>

#define GLSL(src) "#version 150 core\n" #src

const char* default_vert_source =
  GLSL(
       in vec2 position;

       void main() {
	 gl_Position = vec4(position, 0.0f, 1.0f);
       }
       );

const char* default_frag_source =
  GLSL(
       out vec4 outColor;

       void main() {
	 outColor = vec4(255/238, 255/169, 255/89, 1.0f);
       }
       );

Program*
create_program(void* (alloc)(size_t))
{
  Program* program;

  program = (Program*) alloc(sizeof(Program));
  if (program == null)
    {
      fputs("error, can't allocate GL program\n", stderr);
      return null;
    }
  
  program->frag = glCreateShader(GL_FRAGMENT_SHADER);
  program->vert = glCreateShader(GL_VERTEX_SHADER);
  program->program = glCreateProgram();

  return program;
}

int
program_load_default_shaders(Program* program)
{
  if (program == null)
    {
      fputs("error, can't load shaders into null gl program\n", stderr);
      return -0x1;
    }

  glShaderSource(program->vert, 1, &default_vert_source, null);
  glShaderSource(program->frag, 1, &default_frag_source, null);
  
  return 0x0;
}

int
program_link(Program* program)
{
  GLuint position_id;
  glCompileShader(program->vert);
  glCompileShader(program->frag);

  glAttachShader(program->program, program->vert);
  glAttachShader(program->program, program->frag);
  glBindFragDataLocation(program->program, 0x0, "outColor");
  glLinkProgram(program->program);

  glDeleteShader(program->vert);
  glDeleteShader(program->frag);

  use_program(program);
  position_id = glGetAttribLocation(program->program, "position");
  glEnableVertexAttribArray(position_id);
  glVertexAttribPointer(position_id, 0x2, GL_FLOAT, GL_FALSE, 0x0, 0x0);
  return 0x0;
}

int
use_program(Program* program)
{
  glUseProgram(program->program);
  return 0x0;
}

int
delete_program(Program* program)
{
  if (program == null)
    {
#ifdef DEBUG
      fputs("warn, program already deleted\n", stderr);
#endif
      return 0x0;
    }
  
  glDeleteProgram(program->program);

  return 0x0;
}
