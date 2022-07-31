
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory>

#include "cglfw/cglfw.hh"
#include "cglfw/cglfwwindow.hh"
#include "cgl/cgl.hh"

int32_t
main(void)
{
  std::shared_ptr<Cglfw> cglfw;
  std::shared_ptr<CglfwWindow> cwindow;
  std::shared_ptr<Cgl> cgl;

  cglfw = std::make_shared<Cglfw>();
  cwindow = std::make_shared<CglfwWindow>("test", 400, 400);
  cwindow->bind();
  cgl = std::make_shared<Cgl>();

  while (!cwindow->shouldClose())
    {
      cwindow->bind();
      cgl->clear();
      cwindow->present();
      cglfw->pollEvents();
    }
  return 0;
}
