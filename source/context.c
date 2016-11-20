#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include "shader_bakery.h"

struct sb_context_s {
  GLFWwindow* window;
};

sb_context* sb_context_create(sb_options* options)
{
  assert(options != NULL);

  sb_context* context = malloc(sizeof(sb_context));

  if (!glfwInit())
  {
    printf("glfwInit error!\n");
    free(context);
    return NULL;
  }

  if (!options->use_display)
  {
    glfwWindowHint(GLFW_VISIBLE, 0);
  }

  int w = options->width;
  int h = options->height;
  context->window = glfwCreateWindow(w, h, "Bakery", NULL, NULL);

  if (context->window == NULL)
  {
    printf("glfwCreateWindow error!\n");
    glfwTerminate();
    free(context);
    return NULL;
  }

  glfwMakeContextCurrent(context->window);

  return context;
}

void sb_context_draw(sb_context* context, sb_shader* shader, sb_quad* quad)
{
  assert(context != NULL);
  assert(shader != NULL);
  assert(quad != NULL);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  sb_shader_use(shader);
  sb_quad_draw(quad);
  glfwSwapBuffers(context->window);
}

void sb_context_show(sb_context* context)
{
  assert(context != NULL);
  while (!glfwWindowShouldClose(context->window))
  {
    glfwWaitEvents();
  }
}
void sb_context_delete(sb_context* context)
{
  assert(context != NULL);
  glfwDestroyWindow(context->window);
  glfwTerminate();
  free(context);
}
