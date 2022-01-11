#include "shg_utils.h"

void add_vertex(float x, float z, Vertex *vertex, uint32_t vertices_count, uint32_t size) {
  glm_vec3_copy((vec3){ ((float)x / ((float)vertices_count-1) * (float)size),0,((float)z / ((float)vertices_count-1) * (float)size)}, vertex->position);
  glm_vec3_copy((vec3){0, 0, 0}, vertex->normal);
  glm_vec2_copy((vec2){0, 0}, vertex->uv);
}

Vertex *get_cube_vertices() {
  Vertex *vertices;

  float cube_vertices[] = {
      // positions
      -1.0f,  1.0f, -1.0f,
      -1.0f, -1.0f, -1.0f,
      1.0f, -1.0f, -1.0f,
      1.0f, -1.0f, -1.0f,
      1.0f,  1.0f, -1.0f,
      -1.0f,  1.0f, -1.0f,

      -1.0f, -1.0f,  1.0f,
      -1.0f, -1.0f, -1.0f,
      -1.0f,  1.0f, -1.0f,
      -1.0f,  1.0f, -1.0f,
      -1.0f,  1.0f,  1.0f,
      -1.0f, -1.0f,  1.0f,

      1.0f, -1.0f, -1.0f,
      1.0f, -1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,
      1.0f,  1.0f, -1.0f,
      1.0f, -1.0f, -1.0f,

      -1.0f, -1.0f,  1.0f,
      -1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,
      1.0f, -1.0f,  1.0f,
      -1.0f, -1.0f,  1.0f,

      -1.0f,  1.0f, -1.0f,
      1.0f,  1.0f, -1.0f,
      1.0f,  1.0f,  1.0f,
      1.0f,  1.0f,  1.0f,
      -1.0f,  1.0f,  1.0f,
      -1.0f,  1.0f, -1.0f,

      -1.0f, -1.0f, -1.0f,
      -1.0f, -1.0f,  1.0f,
      1.0f, -1.0f, -1.0f,
      1.0f, -1.0f, -1.0f,
      -1.0f, -1.0f,  1.0f,
      1.0f, -1.0f,  1.0f
  };

  return vertices;
}

Mesh get_plane_vertices(uint32_t size, uint32_t vertices_length) {
  Vertex *plane_vertices = malloc(sizeof(Vertex) * ((vertices_length - 1) * (vertices_length - 1)) * 6);
  uint32_t index = 0;
  for(int i = 0; i < vertices_length-1; i++) {
    for (int j = 0; j < vertices_length-1; j++) {
      add_vertex(i, j, &plane_vertices[index++], vertices_length, size);
      add_vertex(i, j+1, &plane_vertices[index++], vertices_length, size);
      add_vertex(i+1, j+1, &plane_vertices[index++], vertices_length, size);

      add_vertex(i, j, &plane_vertices[index++], vertices_length, size);
      add_vertex(i+1, j, &plane_vertices[index++], vertices_length, size);
      add_vertex(i+1, j+1, &plane_vertices[index++], vertices_length, size);
    }
  }

  Mesh mesh = {0};
  mesh.vertices = plane_vertices;
  mesh.vertex_count = index;

  return mesh;
}
