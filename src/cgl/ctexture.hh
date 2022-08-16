
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
  
  void draw(glm::vec2 pos, float rotate, glm::vec2 size,
            glm::vec3 color);
  
private:
  class Impl;
  std::unique_ptr<Impl> impl;
};

#endif
