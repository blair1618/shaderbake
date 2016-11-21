#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include "lodepng.h"
#include "shaderbake.h"

int sb_image_save(sb_framebuffer* framebuffer, sb_options* options)
{
  assert(framebuffer != NULL);
  assert(options != NULL);
  size_t size = sb_framebuffer_data_size(framebuffer);
  void* data = malloc(size);
  sb_framebuffer_data_copy(framebuffer, data);
  const char* filename = "out.png";
  if (options->output_image_file)
  {
    filename = options->output_image_file;
  }
  int stride = options->width * 4;
  assert(stride > 0);
  void* row = malloc((size_t)stride);
  for (size_t pos = 0; pos < size / 2; pos += stride)
  {
    void* upper = data + pos;
    void* lower = data + size - pos - stride;
    memcpy(row, upper, stride);
    memcpy(upper, lower, stride);
    memcpy(lower, row, stride);
  }
  assert(options->width > 0);
  assert(options->height > 0);
  unsigned int width = (unsigned int)options->width;
  unsigned int height = (unsigned int)options->height;
  return lodepng_encode_file(filename, data, width, height, LCT_RGBA, 8);
}
