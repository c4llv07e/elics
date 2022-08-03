
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory>
#include <math.h>

#include "cglfw/cglfw.hh"
#include "cglfw/cglfwwindow.hh"
#include "cgl/cgl.hh"
#include "cgl/cvao.hh"
#include "cgl/cshader.hh"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int32_t
main(void)
{
  std::shared_ptr<Cglfw> cglfw;
  std::shared_ptr<CglfwWindow> cwindow;
  std::shared_ptr<Cgl> cgl;
  std::shared_ptr<Cvao> cvao;
  std::shared_ptr<Cshader> cshader;
  float anim;

  cglfw = std::make_shared<Cglfw>();
  cwindow = std::make_shared<CglfwWindow>("test", 400, 400);
  cwindow->bind();
  cgl = std::make_shared<Cgl>();
  cvao = std::make_shared<Cvao>();
  cshader = std::make_shared<Cshader>();

  cvao->addVbo({
      -0.5f, 0.5f,
      -0.5f, -0.5f,
      0.5f, 0.5f,
      0.5f, -0.5f,
    }, 2);

  cvao->addVbo({
      1.0f, 0.0f, 0.0f,
      1.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 1.0f,
    }, 3);

  cvao->addEbo({
      0, 1, 2,
      2, 1, 3,
    });

  cshader->bindAttr(0, "position");
  cshader->bindAttr(1, "color");
  cshader->link();

  anim = 0;
  while (!cwindow->shouldClose())
    {
      glm::mat4 transform;
      transform = glm::mat4(1.0f);
      transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
      transform = glm::rotate(transform, anim, glm::vec3(0.0f, 0.0f, 1.0f));
      
      anim += 0.01f;
      
      cwindow->bind();
      cgl->clear();
      
      cshader->setMat4("transform", transform);
      cshader->use();
      cvao->draw();
      
      cwindow->present();
      cglfw->pollEvents();
    }
  return 0;
}
