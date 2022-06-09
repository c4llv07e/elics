
#include "vao.hh"

#include <GL/glew.h>
#include <GL/gl.h>

#include <stdio.h>

Vao*
create_vao(void* (alloc)(size_t))
{
  Vao* vao;
  vao = (Vao*) alloc(sizeof(Vao));
  if (vao == null)
    {
      fputs("error, can't allocate vao\n", stderr);
      return vao;
    }
  glGenVertexArrays(1, &(vao->vao));
  glBindVertexArray(vao->vao);

  glGenBuffers(1, &(vao->vbo));

  return vao;
}

int
vao_set_verts(Vao* vao, float* verts, size_t verts_size)
{
  glBindBuffer(GL_ARRAY_BUFFER, vao->vbo);
  glBufferData(GL_ARRAY_BUFFER, verts_size, verts, GL_STATIC_DRAW);
  return 0x0;
}
