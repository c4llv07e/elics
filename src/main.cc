
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory>

#include "cglfw/cglfw.hh"
#include "cglfw/cglfwwindow.hh"
#include "cgl/cgl.hh"
#include "cgl/cvao.hh"

int32_t
main(void)
{
  std::shared_ptr<Cglfw> cglfw;
  std::shared_ptr<CglfwWindow> cwindow;
  std::shared_ptr<Cgl> cgl;
  std::shared_ptr<Cvao> cvao;

  cglfw = std::make_shared<Cglfw>();
  cwindow = std::make_shared<CglfwWindow>("test", 400, 400);
  cwindow->bind();
  cgl = std::make_shared<Cgl>();
  cvao = std::make_shared<Cvao>();

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

  while (!cwindow->shouldClose())
    {
      cwindow->bind();
      cgl->clear();
      cvao->draw();
      cwindow->present();
      cglfw->pollEvents();
    }
  return 0;
}
