
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

  void setProjection(glm::mat4 projection);
  
  void draw(glm::vec2 pos, glm::vec2 size = glm::vec2(10.0f, 10.0f),
            float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
  
private:
  class Impl;
  std::unique_ptr<Impl> impl;
};

#endif
