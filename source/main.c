#include <stdio.h>
#include <SDL2/SDL_events.h>
#include "shader_bakery.h"

int main(int argc, char** argv)
{
  sb_options* options = sb_options_create();
  sb_options_parse(options, argc, argv);

  sb_context* context = sb_context_create(options);

  if (context == NULL)
  {
    printf("Error creating context!\n");
    return 1;
  }
  printf("Created a context!\n");

  sb_shader* shader = sb_shader_create("void main() { gl_FragColor = vec4(0.5); }", -1);

  if (shader == NULL)
  {
    printf("Error creating shader!\n");
    return 1;
  }
  printf("Created a shader!\n");

  sb_quad* quad = sb_quad_create();

  if (quad == NULL)
  {
    printf("Error creating quad!\n");
    return 1;
  }
  printf("Created a quad!\n");

  sb_context_draw(context, shader, quad);
  SDL_Event event;
  do
  {
    SDL_WaitEvent(&event);
  }
  while (event.type != SDL_QUIT);

  sb_quad_delete(quad);
  sb_shader_delete(shader);
  sb_options_delete(options);
  sb_context_delete(context);

  return 0;
}
