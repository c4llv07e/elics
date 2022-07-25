
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory>

#include "cglfw/cglfw.hh"

int32_t
main(void)
{
  std::shared_ptr<Cglfw> cglfw;
  std::shared_ptr<CglfwWindow> cwindow;

  cglfw = std::make_shared<Cglfw>();
  cwindow = std::make_shared<CglfwWindow>("test", 1, 1);
  return 0;
}
