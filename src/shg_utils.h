/**
 * @file shg_utils.h
 * @author Robert Lemmens
 * @date 11-1-2022
 * @brief shg_utils module.
 *
 * Utility functions to quickly create primitives and other helpful shortcuts.
 */
#ifndef SHADER_GUIDE_SHG_UTILS_H
#define SHADER_GUIDE_SHG_UTILS_H
#include "stdint.h"
#include "stdlib.h"
#include "cglm/cglm.h"

typedef struct vertex_s {
  vec3 position;
  vec3 normal;
  vec2 uv;
} Vertex;

typedef struct mesh_s {
  Vertex *vertices;
  uint32_t vertex_count;
} Mesh;

Vertex *get_cube_vertices();
Mesh get_plane_vertices(uint32_t size, uint32_t vertices_length);
#endif //SHADER_GUIDE_SHG_UTILS_H
