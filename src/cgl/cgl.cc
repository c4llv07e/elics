
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>

#include "cgl.hh"
#include <assert.h>

class Cgl::Impl
{
public:
};

Cgl::Cgl(void)
  : impl(std::make_unique<Impl>())
{
  assert(impl);
}

Cgl::~Cgl(void)
{

}

void
Cgl::clear(void)
{
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}
