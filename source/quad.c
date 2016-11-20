#include <assert.h>
#include <stdlib.h>
#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>
#include "shader_bakery.h"

struct sb_quad_s {
  GLuint vertices;
  GLuint indices;
};

const GLfloat vertices[] = {
    -1.f,  1.f,
    -1.f, -1.f,
    1.f, -1.f,
    1.f,  1.f,
};

const GLushort indices[] = {
    0, 1, 2, 2, 3, 0
};

sb_quad* sb_quad_create()
{
  sb_quad* quad = malloc(sizeof(sb_quad));
  quad->vertices = 0;
  quad->indices = 0;
  // Buffer vertices.
  {
    glGenBuffers(1, &quad->vertices);
    glBindBuffer(GL_ARRAY_BUFFER, quad->vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  }
  // Buffer indices.
  {
    glGenBuffers(1, &quad->indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad->indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  }
  return quad;
}

void sb_quad_draw(sb_quad* quad)
{
  assert(quad != NULL);
  glBindBuffer(GL_ARRAY_BUFFER, quad->vertices);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad->indices);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

void sb_quad_delete(sb_quad* quad)
{
  assert(quad != NULL);
  glDeleteBuffers(1, &quad->vertices);
  glDeleteBuffers(1, &quad->indices);
  free(quad);
}
