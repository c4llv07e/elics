
#include "ctexture.hh"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <assert.h>
#include "cvao.hh"
#include "cprogram.hh"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>

const char vert[] = "#version 330 core\n"
  "in vec3 aPos;\n"
  "in vec3 aColor;\n"
  "in vec2 aTexCoord;\n"
  "\n"
  "out vec3 ourColor;\n"
  "out vec2 TexCoord;\n"
  "\n"
  "void main()\n"
  "{\n"
  "    gl_Position = vec4(aPos, 1.0);\n"
  "    ourColor = aColor;\n"
  "    TexCoord = aTexCoord;\n"
  "}\n\0";

const char frag[] = "#version 330 core\n"
  "out vec4 FragColor;\n"
  "\n"
  "in vec3 ourColor;\n"
  "in vec2 TexCoord;\n"
  "\n"
  "uniform sampler2D ourTexture;\n"
  "\n"
  "void main()\n"
  "{\n"
  "    FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0f);\n"
  "}\n\0";

const std::vector<float> positions = {
  1.0f, 1.0f,
  1.0f, -1.0f,
  -1.0f, -1.0f,
  -1.0f, 1.0f,
};

const std::vector<float> colors = {
  1.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f,
  1.0f, 0.0f, 1.0f,
  1.0f, 1.0f, 0.0f,
};

const std::vector<float> uv_map = {
  1.0f, 1.0f,
  1.0f, 0.0f,
  0.0f, 0.0f,
  0.0f, 1.0f,
};

GLuint
createTexture(unsigned char* data, int width, int height)
{
  GLuint texture;
  
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width,
               height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  
  return texture;
}

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
  impl->program->addShader(frag, ShaderFragment);
  impl->program->addShader(vert, ShaderVertex);
  impl->program->bindAttr(0, "aPos");
  impl->program->bindAttr(1, "aColor");
  impl->program->bindAttr(2, "aTexCoord");
  impl->program->link();

  stbi_set_flip_vertically_on_load(true);
  data = stbi_load(path, &impl->width,
                   &impl->height, &impl->nrChannels, 0);
  assert(data);

  impl->texture = createTexture(data, impl->width, impl->height);
  
  stbi_image_free(data);

  impl->vao->addVbo(positions, 2);
  impl->vao->addVbo(colors, 3);
  impl->vao->addVbo(uv_map, 2);

  impl->vao->addEbo({0, 1, 3, 1, 2, 3});
}

void
Ctexture::draw()
{
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, impl->texture);
  impl->program->use();
  impl->vao->draw();
}

Ctexture::~Ctexture(void)
{
  glDeleteTextures(1, &impl->texture);
}
