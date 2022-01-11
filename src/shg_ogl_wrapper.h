/**
 * @file shg_ogl_wrapper.h
 * @author Robert Lemmens
 * @date 11-1-2022
 * @brief shg_ogl_wrapper module.
 *
 * Description
 */
#ifndef SHADER_GUIDE_SHG_OGL_WRAPPER_H
#define SHADER_GUIDE_SHG_OGL_WRAPPER_H
#include "stdint.h"
#include "stdio.h"
#include "stdbool.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "shg_utils.h"
#include "cglm/cglm.h"
#include "shg_camera.h"

void ogl_bind_shader(GLuint shader_id);
void ogl_clear(float r, float g, float b);

GLuint ogl_generate_vertex_array();
GLuint ogl_generate_buffer(uint32_t size, void *data);
GLuint ogl_generate_element_buffer(uint32_t size, void *data);
void ogl_bind_shape(GLuint vao, GLuint vbo);
void ogl_draw_triangles(uint32_t size);
GLuint ogl_compile_shader(const char *fragment_path, const char *vertex_path, const char *geometry_path);
GLint ogl_get_uniform_location(GLuint shader_id, const char *location_name);
void ogl_upload_mat4(GLint location_id, mat4 uniform);

#endif //SHADER_GUIDE_SHG_OGL_WRAPPER_H
