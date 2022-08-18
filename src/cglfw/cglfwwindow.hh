
#ifndef C4LL_CGLFW_WINDOW_INC
#define C4LL_CGLFW_WINDOW_INC

#include <stdint.h>
#include <memory>

class CglfwWindow
{
public:
  CglfwWindow(const char* title, int32_t w, int32_t h);
  ~CglfwWindow(void);
  CglfwWindow(const CglfwWindow&) = delete;
  
  bool shouldClose(void);
  void bind(void);
  void present(void);
  void setOnWindowResize(void (*func)(CglfwWindow*, int, int));
  void (*windowResize)(CglfwWindow*, int, int);
private:
  class Impl;
  std::unique_ptr<Impl> impl;
};

#endif
