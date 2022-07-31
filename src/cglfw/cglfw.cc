
#include "cglfw.hh"
#include <stdint.h>
#include <assert.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

Cglfw::Cglfw(void)
{
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
