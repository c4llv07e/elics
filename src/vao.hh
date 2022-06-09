
#ifndef C4LL_VAO_INC
#define C4LL_VAO_INC

#include <GL/glew.h>
#include <GL/gl.h>

#include "base_types.hh"

typedef struct Vao
{
  GLuint vao;
  GLuint vbo;
} Vao;

Vao* create_vao(void* (alloc)(size_t));
int vao_set_verts(Vao* vao, float* verts, size_t verts_size);

#endif
