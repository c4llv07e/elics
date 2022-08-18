
#ifndef C4LL_CGLFW_WINDOW_INC
#define C4LL_CGLFW_WINDOW_INC

#include <stdint.h>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class CglfwWindow
{
public:
  CglfwWindow(const char* title, int32_t w, int32_t h);
  ~CglfwWindow(void);
  CglfwWindow(const CglfwWindow&) = delete;
  
  bool shouldClose(void);
  void bind(void);
  void present(void);
  void setOnResize(void (*func)(CglfwWindow*, int, int));
  void (*windowResize)(CglfwWindow*, int, int);
  glm::vec2 getSize(void);
private:
  class Impl;
  std::unique_ptr<Impl> impl;
};

#endif
