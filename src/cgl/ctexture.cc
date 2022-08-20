
#include "ctexture.hh"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <assert.h>
#include <stdio.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>

GLuint
createTexture(unsigned char* data, int width, int height, int channels)
{
  GLuint texture;
  GLenum image_type;

  switch (channels)
    {
    case 3:
      image_type = GL_RGB;
      break;
    case 4:
      image_type = GL_RGBA;
      break;
    default:
      /* fallback */
      image_type = GL_RGB;
      break;
    }
  
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  glTexImage2D(GL_TEXTURE_2D, 0, image_type, width,
               height, 0, image_type, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  
  return texture;
}

class Ctexture::Impl
{
public:
  int width, height, nrChannels;
  GLuint texture;
};

Ctexture::Ctexture(const char* path)
  : impl(std::make_unique<Impl>())
{
  unsigned char* data;
  
  assert(impl);

  stbi_set_flip_vertically_on_load(false);
  data = stbi_load(path, &impl->width,
                   &impl->height, &impl->nrChannels, 0);
  assert(data);

  impl->texture = createTexture(data, impl->width, impl->height,
                                impl->nrChannels);
  
  stbi_image_free(data);
}

void
Ctexture::bind(void)
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, impl->texture);
}

Ctexture::~Ctexture(void)
{
  glDeleteTextures(1, &impl->texture);
}
