
#include "ctexture.hh"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <assert.h>

class Ctexture::Impl
{
public:
  int width, height, nrChannels;
};

Ctexture::Ctexture(const char* path)
  : impl(std::make_unique<Impl>())
{
  unsigned char* data;
  GLuint texture;
  
  assert(impl);

  data = stbi_load(path, &impl->width,
                   &impl->height, &impl->nrChannels, 0);
  assert(data);

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, impl->width,
               impl->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
}
