
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>

#include "cgl.hh"
#include <assert.h>
#include <stdio.h>

Cgl::Cgl(void)
{
  GLenum glewError;
  glewExperimental = GL_TRUE;
  glewError = glewInit();
  if (glewError != GLEW_OK && glewError != 4)
    {
      fprintf(stderr, "error, can't init glew(%d): %s\n",
	      glewError, glewGetErrorString(glewError));
    }
}

Cgl::~Cgl(void)
{

}

void
Cgl::clear(void)
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}
