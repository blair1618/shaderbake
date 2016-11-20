#include <assert.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "shader_bakery.h"

struct sb_context_s {
  SDL_Window* window;
  SDL_GLContext glcontext;
};

sb_context* sb_context_create(sb_options* options)
{
  assert(options != NULL);

  sb_context* context = malloc(sizeof(sb_context));

  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    printf("SDL_Init error: %s\n", SDL_GetError());
    free(context);
    return NULL;
  }

  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
  SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

  int x = SDL_WINDOWPOS_CENTERED;
  int y = SDL_WINDOWPOS_CENTERED;
  int w = options->width;
  int h = options->height;
  context->window = SDL_CreateWindow("Bakery", x, y, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

  if (context->window == NULL)
  {
    printf("SDL_CreateWindow error: %s\n", SDL_GetError());
    SDL_Quit();
    free(context);
    return NULL;
  }

  context->glcontext = SDL_GL_CreateContext(context->window);

  if (context->glcontext == NULL)
  {
    printf("SDL_GL_CreateContext error: %s\n", SDL_GetError());
    SDL_DestroyWindow(context->window);
    SDL_Quit();
    free(context);
    return NULL;
  }

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
  SDL_GL_SwapWindow(context->window);
}

void sb_context_delete(sb_context* context)
{
  assert(context != NULL);
  SDL_GL_DeleteContext(context->glcontext);
  SDL_DestroyWindow(context->window);
  SDL_Quit();
  free(context);
}
