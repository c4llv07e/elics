
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>

#include "cvao.hh"
#include <assert.h>

class Cvao::Impl
{
public:
  GLuint vao;
  GLuint ebo;
  size_t ebo_count;
  std::vector<GLuint> buffers;
};

Cvao::Cvao(void)
  : impl(std::make_unique<Impl>())
{
  assert(impl);
  impl->buffers = std::vector<GLuint>(0);
  glGenVertexArrays(1, &(impl->vao));
}

Cvao::~Cvao(void)
{
  glDeleteBuffers(impl->buffers.size(), impl->buffers.data());
  glDeleteBuffers(1, &impl->ebo);
  glDeleteVertexArrays(1, &impl->vao);
}

void
Cvao::bind(void)
{
  glBindVertexArray(impl->vao);
}

void
Cvao::draw(void)
{
  assert(impl->ebo);
  bind();
  for (size_t i = 0; i < impl->buffers.size(); ++i)
    glEnableVertexAttribArray(i);

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); /* debug */
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, impl->ebo);
  glDrawElements(GL_TRIANGLES, impl->ebo_count,
		 GL_UNSIGNED_INT, nullptr);
  
  for (size_t i = 0; i < impl->buffers.size(); ++i)
    glDisableVertexAttribArray(i);
}

void
Cvao::addVbo(const std::vector<float>& data, size_t groupLen)
{
  GLuint vbo;
  bind();
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float),
	       data.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(impl->buffers.size(), groupLen, GL_FLOAT, GL_FALSE,
			groupLen * sizeof(float), nullptr);
  impl->buffers.push_back(vbo);
}

void
Cvao::addEbo(const std::vector<unsigned int>& data)
{
  assert(impl->ebo == 0);
  bind();
  
  impl->ebo_count = data.size();
  glGenBuffers(1, &impl->ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, impl->ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned), data.data(), GL_STATIC_DRAW);
}
