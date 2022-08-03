
#include "cglfw.hh"
#include <stdint.h>
#include <assert.h>
#include <stdio.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

void
onGlfwError(int code, const char* message)
{
  fprintf(stderr, "glfw error(%d): %s\n", code, message);
}

Cglfw::Cglfw(void)
{
  glfwSetErrorCallback(onGlfwError);
  assert(glfwInit() == GLFW_TRUE);
}

Cglfw::~Cglfw(void)
{
  glfwTerminate();
}

void
Cglfw::pollEvents(void)
{
  glfwPollEvents();
}
