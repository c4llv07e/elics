
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory>
#include <math.h>

#include "cglfw/cglfw.hh"
#include "cglfw/cglfwwindow.hh"
#include "cgl/cgl.hh"
#include "cgl/ctexture.hh"
#include "cgl/ctexmanager.hh"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

std::shared_ptr<CtexManager> ctexmanager;

void
onResize(CglfwWindow* win, int w, int h)
{
  if (ctexmanager != nullptr)
    ctexmanager->setProjection(glm::ortho(0.0f, (float)w,
                                          (float)h, 0.0f,
                                          -1.0f, 1.0f));
}

int32_t
main(void)
{
  std::shared_ptr<Cglfw> cglfw;
  std::shared_ptr<CglfwWindow> cwindow;
  std::shared_ptr<Cgl> cgl;
  std::shared_ptr<Ctexture> ctexture;
  std::shared_ptr<Ctexture> ctexture2;

  cglfw = std::make_shared<Cglfw>();
  cwindow = std::make_shared<CglfwWindow>("test", 400, 400);
  cwindow->bind();
  cgl = std::make_shared<Cgl>();
  ctexture = std::make_shared<Ctexture>("./test_texture.png");
  ctexture2 = std::make_shared<Ctexture>("./test_texture2.png");
  ctexmanager = std::make_shared<CtexManager>();

  cwindow->setOnResize(onResize);

  while (!cwindow->shouldClose())
    {
      glm::vec2 winSize;
      winSize = cwindow->getSize();
      cwindow->bind();
      cgl->clear();

      ctexmanager->draw(ctexture,
                        winSize / 2.0f,
                        glm::vec2(200.0f + glm::cos(cglfw->getTime()
                                                    * 6) * 20.0f),
                        cglfw->getTime() * 100.0f,
                        {glm::sin((0.3f
                                   + cglfw->getTime()) * 3) / 2 + 0.5f,
                         glm::sin((1.6f
                                   + cglfw->getTime()) * 5) / 2 + 0.5f,
                         glm::sin(cglfw->getTime() * 1) / 2 + 0.5f,
                         1.0f});

      ctexmanager->draw(ctexture2,
                        winSize * 4.0f / 5.0f,
                        glm::vec2(100.0f));
      
      cwindow->present();
      cglfw->pollEvents();
    }
  return 0;
}
