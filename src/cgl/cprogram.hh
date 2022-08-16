
#ifndef C4LL_CPROGRAM_INC
#define C4LL_CPROGRAM_INC

#include <stdint.h>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

typedef enum ShaderType
  {
    ShaderFragment,
    ShaderVertex,
  } ShaderType;

class Cprogram
{
public:
  Cprogram(void);
  ~Cprogram(void);
  Cprogram(const Cprogram&) = delete;

  void addShader(const char* source, ShaderType type);
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
