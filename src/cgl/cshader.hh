
#ifndef C4LL_CSHADER_INC
#define C4LL_CSHADER_INC

#include <stdint.h>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Cshader
{
public:
  Cshader(void);
  ~Cshader(void);
  Cshader(const Cshader&) = delete;

  void link(void);
  void use(void);
  void bindAttr(unsigned int ind, const char* name);
  void setFloat(const char* name, float value);
  void setMat4(const char* name, glm::mat4 value);
private:
  class Impl;
  std::unique_ptr<Impl> impl;
};

#endif
