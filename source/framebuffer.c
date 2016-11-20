#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>
#include "shaderbake.h"


struct sb_framebuffer_s {
  GLuint handle;
  GLuint texture;
  GLsizei size;
};

sb_framebuffer* sb_framebuffer_create(sb_options* options)
{
  assert(options != NULL);
  sb_framebuffer* framebuffer = malloc(sizeof(sb_framebuffer));
  glGenFramebuffers(1, &framebuffer->handle);
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->handle);
  glGenTextures(1, &framebuffer->texture);
  glBindTexture(GL_TEXTURE_2D, framebuffer->texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  int width = options->width;
  int height = options->height;
  framebuffer->size = width * height * 4;
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebuffer->texture, 0);
  GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (status != GL_FRAMEBUFFER_COMPLETE)
  {
    printf("Framebuffer incomplete!\n");
    sb_framebuffer_delete(framebuffer);
    return NULL;
  }
  return framebuffer;
}

size_t sb_framebuffer_data_size(sb_framebuffer* framebuffer)
{
  assert(framebuffer != NULL);
  assert(framebuffer->size > 0);
  return (size_t)framebuffer->size;
}

void sb_framebuffer_data_copy(sb_framebuffer* framebuffer, void* destination)
{
  assert(framebuffer != NULL);
  glBindTexture(GL_TEXTURE_2D, framebuffer->texture);
  glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, destination);
}

void sb_framebuffer_use(sb_framebuffer* framebuffer)
{
  assert(framebuffer != NULL);
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->handle);
}

void sb_framebuffer_delete(sb_framebuffer* framebuffer)
{
  assert(framebuffer != NULL);
  glDeleteTextures(1, &framebuffer->texture);
  glDeleteFramebuffers(1, &framebuffer->handle);
  free(framebuffer);
}
