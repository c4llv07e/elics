
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>

#include "cshader.hh"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const char* frag_source = "#version 330 core\n"
  "out vec4 color;\n"
  "in vec3 pass_color;\n"
  "void main() {\n"
  "  color = vec4(pass_color, 1.0f);\n"
  "}\n\0";

const char* vert_source = "#version 330 core\n"
  "in vec2 position;\n"
  "in vec3 color;\n"
  "out vec3 pass_color;\n"
  "uniform mat4 transform;\n"
  "void main() {\n"
  "  gl_Position = transform * vec4(position, 0.0f, 1.0f);\n"
  "  pass_color = color;\n"
  "}\n\0";

GLuint
compileShader(const char* source, GLenum type)
{
  GLuint shader;
  GLint status;
  char log[0x200];
  GLsizei len;
  
  shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, nullptr);
  glCompileShader(shader);

  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  glGetShaderInfoLog(shader, sizeof(log), &len, log);

  if (len > 0)
    {
      fprintf(stderr, "warn on shader compile(%d): %s\n", status, log);
    }
  
  if (status == 0)
    {
      fprintf(stderr, "error, can't compile shader\n");
      exit(-1);
    }

  return shader;
}

class Cshader::Impl
{
public:
  GLuint getLocation(const char* name);
  GLuint program;
  GLuint frag, vert;
};

GLuint
Cshader::Impl::getLocation(const char* name)
{
  return glGetUniformLocation(program, name);
}

Cshader::Cshader(void)
  : impl(std::make_unique<Impl>())
{
  impl->program = glCreateProgram();
  impl->vert = compileShader(vert_source, GL_VERTEX_SHADER);
  impl->frag = compileShader(frag_source, GL_FRAGMENT_SHADER);
}

Cshader::~Cshader(void)
{
  glDeleteProgram(impl->program);
}

void
Cshader::link(void)
{
  GLint status;
  char log[0x200];
  GLsizei len;
  
  glAttachShader(impl->program, impl->vert);
  glAttachShader(impl->program, impl->frag);
  glLinkProgram(impl->program);

  glGetProgramiv(impl->program, GL_LINK_STATUS, &status);
  glGetProgramInfoLog(impl->program, sizeof(log),
		      &len, log);
  if (len > 0)
    {
      fprintf(stderr, "warn on shader compile(%d): %s\n", status, log);
    }
  
  if (status == 0)
    {
      fprintf(stderr, "error, can't compile shader\n");
      exit(-1);
    }
  
  glDeleteShader(impl->vert);
  glDeleteShader(impl->frag);
}

void
Cshader::use(void)
{
  glUseProgram(impl->program);
}

void
Cshader::bindAttr(unsigned int ind, const char* name)
{
  glBindAttribLocation(impl->program, ind, name);
}

void
Cshader::setFloat(const char* name, float value)
{
  glUniform1f(impl->getLocation(name), value);
}

void
Cshader::setMat4(const char* name, glm::mat4 value)
{
  glUniformMatrix4fv(impl->getLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}