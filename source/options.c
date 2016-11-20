#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "shader_bakery.h"

sb_options* sb_options_create()
{
  sb_options* options = malloc(sizeof(sb_options));
  options->output_image_file = NULL;
  options->input_shader_file = NULL;
  options->use_stdin = 0;
  options->width = 256;
  options->height = 256;
  return options;
}

void sb_options_parse(sb_options* options, int argc, char **argv)
{
  assert(options != NULL);
  int c = 0;
  const char* width = NULL;
  const char* height = NULL;
  do
  {
    c = getopt(argc, argv, "w:h:f:o:i");
    switch (c)
    {
    case 'w':
      width = optarg;
      break;
    case 'h':
      height = optarg;
      break;
    case 'f':
      options->input_shader_file = optarg;
      break;
    case 'o':
      options->output_image_file = optarg;
      break;
    case 'i':
      options->use_stdin = 1;
      break;
    default:
      break;
    }
  }
  while (c != -1);

  if (width != NULL)
  {
    options->width = atoi(width);
  }

  if (height != NULL)
  {
    options->height = atoi(height);
  }
}

void sb_options_delete(sb_options* options)
{
  free(options);
}
