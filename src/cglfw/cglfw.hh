
#ifndef C4LL_CGLFW_INC
#define C4LL_CGLFW_INC

#include <stdint.h>
#include <memory>

class Cglfw
{
public:
  Cglfw(void);
  ~Cglfw(void);
  Cglfw(const Cglfw&) = delete;
};

class CglfwWindow
{
public:
  CglfwWindow(const char* title, int32_t w, int32_t h);
  ~CglfwWindow(void);
  CglfwWindow(const CglfwWindow&) = delete;
private:
  class Impl;
  std::unique_ptr<Impl> impl;
};

#endif
