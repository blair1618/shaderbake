#include <stdio.h>
#include <stdlib.h>
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

  sb_shader* shader = NULL;
  if (options->input_shader_file)
  {
    FILE* file = fopen(options->input_shader_file, "rb");
    if (!file)
    {
      printf("Could not open file: %s\n", options->input_shader_file);
    }
    else
    {
      fseek(file, 0, SEEK_END);
      size_t size = (size_t)ftell(file);
      fseek(file, 0, SEEK_SET);
      char* buffer = (char*)malloc(size);
      fread(buffer, 1, size, file);
      fclose(file);
      shader = sb_shader_create(buffer, (int)size);
    }
  }

  if (shader == NULL)
  {
    printf("Error creating shader!\n");
    return 1;
  }

  sb_quad* quad = sb_quad_create();

  if (quad == NULL)
  {
    printf("Error creating quad!\n");
    return 1;
  }

  sb_context_draw(context, shader, quad);
  sb_context_show(context);

  sb_quad_delete(quad);
  sb_shader_delete(shader);
  sb_options_delete(options);
  sb_context_delete(context);

  return 0;
}
