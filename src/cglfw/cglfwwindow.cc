
#include "cglfwwindow.hh"
#include <stdint.h>
#include <assert.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

class CglfwWindow::Impl
{
public:
  GLFWwindow* window;
};

CglfwWindow::CglfwWindow(const char* title, int32_t w, int32_t h)
  : impl (std::make_unique<Impl>())
{
  assert(impl);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  impl->window = glfwCreateWindow(w, h, title, NULL, NULL);
  assert(impl->window);
  glfwMakeContextCurrent(impl->window);
  glewExperimental = true;
  assert(glewInit() == GLEW_OK);
}

CglfwWindow::~CglfwWindow(void)
{
  glfwDestroyWindow(impl->window);
}

bool
CglfwWindow::shouldClose(void)
{
  return glfwWindowShouldClose(impl->window);
}

void
CglfwWindow::bind(void)
{
  glfwMakeContextCurrent(impl->window);
}

void
CglfwWindow::present(void)
{
  glfwSwapBuffers(impl->window);
}
