
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "cobject.hh"
#include "cvao.hh"
#include "cshader.hh"

#include <assert.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Cobject::Impl
{
public:
  std::shared_ptr<Cvao> cvao;
  std::shared_ptr<Cshader> cshader;
  float rotate;
  glm::vec2 translate;
  glm::vec2 scale;
};

Cobject::Cobject(void)
  : impl(std::make_unique<Impl>())
{
  assert(impl);
  impl->cvao = std::make_shared<Cvao>();
  impl->cshader = std::make_shared<Cshader>();
  
  impl->cvao->addVbo({
      -1.0f, 1.0f,
      -1.0f, -1.0f,
      1.0f, 1.0f,
      1.0f, -1.0f,
    }, 2);

  impl->cvao->addVbo({
      1.0f, 0.0f, 0.0f,
      1.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 1.0f,
    }, 3);
  
  impl->cvao->addEbo({
      0, 1, 2,
      2, 1, 3,
    });
  
  impl->cshader->bindAttr(0, "position");
  impl->cshader->bindAttr(1, "color");
  impl->cshader->link();
}

Cobject::~Cobject(void)
{

}

void
Cobject::rotate(float val)
{
  impl->rotate = val;
}

void
Cobject::translate(glm::vec2 val)
{
  impl->translate = val;
}

void
Cobject::scale(float val)
{
  impl->scale = glm::vec2(val, val);
}

void
Cobject::scale(glm::vec2 val)
{
  impl->scale = val;
}

void
Cobject::draw(void)
{
  glm::mat4 transform;
  transform = glm::mat4(1.0f);
  
  transform = glm::translate(transform, glm::vec3(impl->translate, 0.0f));
  transform = glm::rotate(transform,
			  impl->rotate, glm::vec3(0.0f, 0.0f, 1.0f));
  transform = glm::scale(transform, glm::vec3(impl->scale, 1.0f));
  
  impl->cshader->setMat4("transform", transform);
  impl->cshader->use();
  impl->cvao->draw();
}
