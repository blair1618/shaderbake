#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#include "shader_bakery.h"

#define POS_ATTRIBUTE "a_position"

const GLchar* vs_source =
"attribute vec2 " POS_ATTRIBUTE ";\n"
"void main()\n"
"{\n"
"  gl_Position = vec4(a_position, 0., 1.);\n"
"}\n";

struct sb_shader_s {
  GLuint program;
  GLuint vertex;
  GLuint fragment;
};

sb_shader* sb_shader_create(const char* source, int length)
{
  sb_shader* shader = malloc(sizeof(sb_shader));
  shader->program = 0;
  shader->vertex = 0;
  shader->fragment = 0;
  // Compile vertex shader.
  {
    shader->vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader->vertex, 1, &vs_source, NULL);
    glCompileShader(shader->vertex);
    GLint compiled = GL_FALSE;
    glGetShaderiv(shader->vertex, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE)
    {
      GLchar log[1024] = { 0 };
      glGetShaderInfoLog(shader->vertex, sizeof(log), NULL, log);
      printf("Shader did not compile.\n%s\n", log);
      sb_shader_delete(shader);
      return NULL;
    }
  }
  // Compile fragment shader.
  {
    shader->fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader->fragment, 1, &source, &length);
    glCompileShader(shader->fragment);
    GLint compiled = GL_FALSE;
    glGetShaderiv(shader->fragment, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE)
    {
      GLchar log[1024] = { 0 };
      glGetShaderInfoLog(shader->fragment, sizeof(log), NULL, log);
      printf("Shader did not compile.\n%s\n", log);
      sb_shader_delete(shader);
      return NULL;
    }
  }
  // Link the program.
  {
    shader->program = glCreateProgram();
    glBindAttribLocation(shader->program, 0, POS_ATTRIBUTE);
    glEnableVertexAttribArray(0);
    glAttachShader(shader->program, shader->vertex);
    glAttachShader(shader->program, shader->fragment);
    glLinkProgram(shader->program);
    GLint linked = GL_FALSE;
    glGetProgramiv(shader->program, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE)
    {
      GLchar log[1024] = { 0 };
      glGetProgramInfoLog(shader->program, sizeof(log), NULL, log);
      printf("Shader program did not link.\n%s\n", log);
      sb_shader_delete(shader);
      return NULL;
    }
  }
  return shader;
}

void sb_shader_use(sb_shader* shader)
{
  assert(shader != NULL);
  glUseProgram(shader->program);
}

void sb_shader_delete(sb_shader* shader)
{
  assert(shader != NULL);
  glDeleteShader(shader->vertex);
  glDeleteShader(shader->fragment);
  glDeleteProgram(shader->program);
  free(shader);
}
