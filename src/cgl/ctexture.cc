
#include "ctexture.hh"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <assert.h>
#include "cvao.hh"
#include "cprogram.hh"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>

const float positions[] = {
  1.0f, 1.0f,
  1.0f, -1.0f,
  -1.0f, -1.0f,
  -1.0f, 1.0f,
};

const float colors[] = {
  1.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f,
  1.0f, 0.0f, 1.0f,
  1.0f, 1.0f, 0.0f,
};

const float uv_map[] = {
  1.0f, 1.0f,
  1.0f, 0.0f,
  0.0f, 0.0f,
  0.0f, 1.0f,
};

class Ctexture::Impl
{
public:
  int width, height, nrChannels;
  GLuint texture;
  std::shared_ptr<Cvao> vao;
  std::shared_ptr<Cprogram> program;
};

Ctexture::Ctexture(const char* path)
  : impl(std::make_unique<Impl>())
{
  unsigned char* data;
  
  assert(impl);

  impl->vao = std::make_shared<Cvao>();
  impl->program = std::make_shared<Cprogram>();

  data = stbi_load(path, &impl->width,
                   &impl->height, &impl->nrChannels, 0);
  assert(data);

  glGenTextures(1, &impl->texture);
  glBindTexture(GL_TEXTURE_2D, impl->texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, impl->width,
               impl->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
}

Ctexture::~Ctexture(void)
{
  glDeleteTextures(1, &impl->texture);
}
