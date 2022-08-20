
#ifndef C4LL_TEXMANAGER_INC
#define C4LL_TEXMANAGER_INC

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ctexture.hh"

class CtexManager
{
public:
  CtexManager(void);
  ~CtexManager(void);
  CtexManager(const CtexManager&) = delete;
  void setProjection(glm::mat4 projection);
  void draw(std::shared_ptr<Ctexture> texture,
            glm::vec2 pos, glm::vec2 size = glm::vec2(10.0f),
            float rotate = 0.0f, glm::vec4 color = glm::vec4(1.0f));

private:
  class Impl;
  std::unique_ptr<Impl> impl;
};

#endif
