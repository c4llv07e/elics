
#ifndef C4LL_CTEXTURE_INC
#define C4LL_CTEXTURE_INC

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>

class Ctexture
{
public:
  Ctexture(const char* path);
  ~Ctexture(void);
  Ctexture(const Ctexture&) = delete;
  void bind(void);
  
private:
  class Impl;
  std::unique_ptr<Impl> impl;
};

#endif
