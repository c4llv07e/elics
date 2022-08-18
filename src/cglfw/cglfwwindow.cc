
#include <GLFW/glfw3.h>

#include "cglfwwindow.hh"
#include <assert.h>
#include <map>

class CglfwWindow::Impl
{
public:
  GLFWwindow* window;
};

std::map<GLFWwindow*, CglfwWindow*> windowMap;

void
onWindowChangeSize(GLFWwindow* win, int w, int h)
{
  CglfwWindow* cwindow;
  glViewport(0, 0, w, h);

  cwindow = windowMap[win];
  
  if (windowMap[win] != nullptr && windowMap[win]->windowResize != nullptr)
    windowMap[win]->windowResize(windowMap[win], w, h);
}

CglfwWindow::CglfwWindow(const char* title, int32_t w, int32_t h)
  : impl (std::make_unique<Impl>())
{
  assert(impl != nullptr);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  impl->window = glfwCreateWindow(w, h, title, nullptr, nullptr);
  assert(impl->window != nullptr);
  glfwSetFramebufferSizeCallback(impl->window, onWindowChangeSize);
  bind();
  windowMap[impl->window] = this;
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

void
CglfwWindow::setOnWindowResize(void (*func)(CglfwWindow*, int, int))
{
  windowResize = func;
}
