
#ifndef C4LL_COBJECT_INC
#define C4LL_COBJECT_INC

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Cobject
{
public:
  Cobject(void);
  ~Cobject(void);
  Cobject(const Cobject&) = delete;
  void rotate(float val);
  void translate(glm::vec2 val);
  void scale(glm::vec2 val);
  void scale(float val);
  void draw(void);
private:
  class Impl;
  std::unique_ptr<Impl> impl;
};

#endif
