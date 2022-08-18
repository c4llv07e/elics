
#include "ctexture.hh"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <assert.h>
#include <stdio.h>
#include "cvao.hh"
#include "cprogram.hh"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>

const char vert[] = "#version 330 core\n"
  "in vec2 aPos;\n"
  "in vec2 aTexCoord;\n"
  "\n"
  "out vec2 TexCoord;\n"
  "\n"
  "uniform mat4 model;\n"
  "uniform mat4 projection;\n"
  "\n"
  "void main()\n"
  "{\n"
  "    gl_Position = projection * model * vec4(aPos, 0.0f, 1.0f);\n"
  "    TexCoord = aTexCoord;\n"
  "}\n\0";

const char frag[] = "#version 330 core\n"
  "in vec2 TexCoord;\n"
  "\n"
  "out vec4 color;\n"
  "\n"
  "uniform sampler2D image;\n"
  "uniform vec4 sColor;\n"
  "\n"
  "void main()\n"
  "{\n"
  "    color = sColor * texture(image, TexCoord);\n"
  "}\n\0";

const std::vector<float> positions = {
  1.0f, 1.0f,
  1.0f, -1.0f,
  -1.0f, -1.0f,
  -1.0f, 1.0f,
};

const std::vector<float> uv_map = {
  1.0f, 1.0f,
  1.0f, 0.0f,
  0.0f, 0.0f,
  0.0f, 1.0f,
};

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
  impl->program->bindAttr(1, "aTexCoord");
  impl->program->link();

  stbi_set_flip_vertically_on_load(false);
  data = stbi_load(path, &impl->width,
                   &impl->height, &impl->nrChannels, 0);
  assert(data);

  impl->texture = createTexture(data, impl->width, impl->height,
                                impl->nrChannels);
  
  stbi_image_free(data);

  impl->vao->addVbo(positions, 2);
  impl->vao->addVbo(uv_map, 2);

  impl->vao->addEbo({0, 1, 3, 1, 2, 3});
}

void
Ctexture::setProjection(glm::mat4 projection)
{
  impl->program->use();
  impl->program->setMat4("projection", projection);
}

void
Ctexture::draw(glm::vec2 pos, glm::vec2 size, float rotate,
               glm::vec4 color)
{
  glm::mat4 model;

  model = glm::mat4(1.0f);

  model = glm::translate(model, glm::vec3(pos, 0.0f));
  model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::scale(model, glm::vec3(size, 1.0f));

  impl->program->setMat4("model", model);
  impl->program->setVec4("sColor", color);
  
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, impl->texture);
  impl->program->use();
  impl->vao->draw();
}

Ctexture::~Ctexture(void)
{
  glDeleteTextures(1, &impl->texture);
}
