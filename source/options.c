#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "shader_bakery.h"

sb_options* sb_options_create()
{
  sb_options* options = malloc(sizeof(sb_options));
  options->width = 800;
  options->height = 600;
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
    c = getopt(argc, argv, "w:h:");
    switch (c)
    {
    case 'w':
      width = optarg;
      break;
    case 'h':
      height = optarg;
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
