
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory>
#include <math.h>

#include "cglfw/cglfw.hh"
#include "cglfw/cglfwwindow.hh"
#include "cgl/cgl.hh"
#include "cgl/cobject.hh"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int32_t
main(void)
{
  std::shared_ptr<Cglfw> cglfw;
  std::shared_ptr<CglfwWindow> cwindow;
  std::shared_ptr<Cgl> cgl;
  std::shared_ptr<Cobject> cobject;

  cglfw = std::make_shared<Cglfw>();
  cwindow = std::make_shared<CglfwWindow>("test", 400, 400);
  cwindow->bind();
  cgl = std::make_shared<Cgl>();
  cobject = std::make_shared<Cobject>();

  cobject->translate({ 0.5f, -0.5f });
  cobject->scale(0.5f);
  
  while (!cwindow->shouldClose())
    {
      cobject->rotate(0.1f);
      
      cwindow->bind();
      cgl->clear();

      cobject->draw();
      
      cwindow->present();
      cglfw->pollEvents();
    }
  return 0;
}
