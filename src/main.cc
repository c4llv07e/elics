
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory>
#include <math.h>

#include "cglfw/cglfw.hh"
#include "cglfw/cglfwwindow.hh"
#include "cgl/cgl.hh"
#include "cgl/ctexture.hh"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void
onResize(CglfwWindow* win, int w, int h)
{
  fprintf(stdout, "resized: %d %d\n", w, h);
}

int32_t
main(void)
{
  std::shared_ptr<Cglfw> cglfw;
  std::shared_ptr<CglfwWindow> cwindow;
  std::shared_ptr<Cgl> cgl;
  std::shared_ptr<Ctexture> ctexture;

  cglfw = std::make_shared<Cglfw>();
  cwindow = std::make_shared<CglfwWindow>("test", 400, 400);
  cwindow->bind();
  cgl = std::make_shared<Cgl>();
  ctexture = std::make_shared<Ctexture>("./test_texture.jpg");

  cwindow->setOnWindowResize(onResize);
  ctexture->setProjection(glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f));
  
  while (!cwindow->shouldClose())
    {
      cwindow->bind();
      cgl->clear();

      ctexture->draw({400.0f, 300.0f}, glm::vec2(100.0f),
                     45.0f, {0.0f, 1.0f, 1.0f, 0.5f});
      
      cwindow->present();
      cglfw->pollEvents();
    }
  return 0;
}
