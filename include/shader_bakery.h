#pragma once

//
// Options
//
typedef struct sb_options_s {
  const char* output_image_file;
  const char* input_shader_file;
  int use_stdin;
  int width;
  int height;
} sb_options;

sb_options* sb_options_create();
void sb_options_parse(sb_options* options, int argc, char **argv);
void sb_options_delete(sb_options* options);

//
// Shader
//
typedef struct sb_shader_s sb_shader;

sb_shader* sb_shader_create(const char* source, int length);
void sb_shader_use(sb_shader* shader);
void sb_shader_delete(sb_shader* shader);

//
// Quad
//
typedef struct sb_quad_s sb_quad;

sb_quad* sb_quad_create();
void sb_quad_draw(sb_quad* quad);
void sb_quad_delete(sb_quad* quad);

//
// Context
//
typedef struct sb_context_s sb_context;

sb_context * sb_context_create(sb_options *options);
void sb_context_draw(sb_context* context, sb_shader* shader, sb_quad* quad);
void sb_context_show(sb_context* context);
void sb_context_delete(sb_context* context);
