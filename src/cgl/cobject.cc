
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
  glm::mat4 transform;
};

Cobject::Cobject(void)
  : impl(std::make_unique<Impl>())
{
  assert(impl);
  impl->cvao = std::make_shared<Cvao>();
  impl->cshader = std::make_shared<Cshader>();
  reset();

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
Cobject::update(void)
{
  impl->cshader->setMat4("transform", impl->transform);
}

void
Cobject::rotate(float val)
{
  impl->transform = glm::rotate(impl->transform, val,
				glm::vec3(0.0f, 0.0f, 1.0f));
}

void
Cobject::translate(glm::vec2 val)
{
  impl->transform = glm::translate(impl->transform,
				   glm::vec3(val, 0.0f));
}

void
Cobject::reset(void)
{
  impl->transform = glm::mat4(1.0f);
}

void
Cobject::scale(float val)
{
  impl->transform = glm::scale(impl->transform,
			       glm::vec3(val, val, 1.0f));
}

void
Cobject::scale(glm::vec2 val)
{
  impl->transform = glm::scale(impl->transform,
			       glm::vec3(val, 1.0f));
}

void
Cobject::draw(void)
{
  update();
  impl->cshader->use();
  impl->cvao->draw();
}
