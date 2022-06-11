#ifndef C4LL_ELEMENT_INC
#define C4LL_ELEMENT_INC

#include "base_types.hh"
#include "opengl/program.hh"
#include "opengl/vao.hh"

typedef struct Element
{
  Vao* vao;
  double x, y, width, height;
} Element;

#endif
