
#include "ctexmanager.hh"

#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include "cvao.hh"
#include "cprogram.hh"

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

class CtexManager::Impl
{
public:
  std::shared_ptr<Cvao> vao;
  std::shared_ptr<Cprogram> program;
};

CtexManager::CtexManager(void)
  : impl (std::make_unique<Impl>())
{
  assert(impl != nullptr);
  
  impl->vao = std::make_shared<Cvao>();
  impl->program = std::make_shared<Cprogram>();
  impl->program->addShader(frag, ShaderFragment);
  impl->program->addShader(vert, ShaderVertex);
  impl->program->bindAttr(0, "aPos");
  impl->program->bindAttr(1, "aTexCoord");
  impl->program->link();

  impl->vao->addVbo(positions, 2);
  impl->vao->addVbo(uv_map, 2);

  impl->vao->addEbo({0, 1, 3, 1, 2, 3});
}

CtexManager::~CtexManager(void)
{
}

void
CtexManager::setProjection(glm::mat4 projection)
{
  impl->program->use();
  impl->program->setMat4("projection", projection);
}

void
CtexManager::draw(std::shared_ptr<Ctexture> texture,
                  glm::vec2 pos, glm::vec2 size,
                  float rotate, glm::vec4 color)
{
  glm::mat4 model;

  model = glm::mat4(1.0f);

  model = glm::translate(model, glm::vec3(pos, 0.0f));
  model = glm::rotate(model, glm::radians(rotate),
                      glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::scale(model, glm::vec3(size, 1.0f));
  
  impl->program->setMat4("model", model);
  impl->program->setVec4("sColor", color);

  texture->bind();
  impl->program->use();
  impl->vao->draw();
}
