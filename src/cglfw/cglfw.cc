
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
  return;
}

Cglfw::~Cglfw(void)
{
  glfwTerminate();
  return;
}

class CglfwWindow::Impl
{
public:
  GLFWwindow* window;
};

CglfwWindow::CglfwWindow(const char* title, int32_t w, int32_t h)
  : impl (std::make_unique<Impl>())
{
  assert(impl);
  impl->window = glfwCreateWindow(w, h, title, NULL, NULL);
  return;
}

CglfwWindow::~CglfwWindow(void)
{
  return;
}
