#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "shaderbake.h"

const char* help =
"Usage: shader2png [options] <infile>\n"
"Options:\n"
"  <infile>     = Input GLSL fragment shader file.\n"
"  -o <outfile> = Set output image file to <file>. Default is 'out.png'.\n"
"  -w <width>   = Set output image width to <width> pixels. Default is 256.\n"
"  -h <height>  = Set output image height to <height> pixels. Default is 256.\n"
"  -i           = Use stdin as input file (ignores <infile> argument).\n"
"  -d           = Display the output image instead of saving to a file.\n";

sb_options* sb_options_create()
{
  sb_options* options = malloc(sizeof(sb_options));
  options->output_image_file = NULL;
  options->input_shader_file = NULL;
  options->use_stdin = 0;
  options->use_display = 0;
  options->width = 256;
  options->height = 256;
  return options;
}

const char* sb_options_help_string()
{
  return help;
}

void sb_options_parse(sb_options* options, int argc, char **argv)
{
  assert(options != NULL);
  int c = 0;
  const char* width = NULL;
  const char* height = NULL;
  while (c != -1)
  {
    c = getopt(argc, argv, "w:h:o:id");
    switch (c)
    {
    case 'w':
      width = optarg;
      break;
    case 'h':
      height = optarg;
      break;
    case 'o':
      options->output_image_file = optarg;
      break;
    case 'i':
      options->use_stdin = 1;
      break;
    case 'd':
      options->use_display = 1;
      break;
    default:
      break;
    }
  }
  if (width != NULL)
  {
    options->width = atoi(width);
  }
  if (height != NULL)
  {
    options->height = atoi(height);
  }
  if (argc > optind && !options->use_stdin)
  {
    options->input_shader_file = argv[optind];
  }
}

void sb_options_delete(sb_options* options)
{
  assert(options != NULL);
  free(options);
}
