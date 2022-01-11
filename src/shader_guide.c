#include <stdio.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "shg_utils.h"
#include "shg_ogl_wrapper.h"
#include "shg_camera.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 720

// Our camera
static Camera camera;

void update_camera(GLFWwindow *window, float dt) {
  static bool first_click = true;
  if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS) {
    double xpos, ypos;
    static double previous_xpos, previous_ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    if (first_click) {
      first_click = false;
      previous_xpos = xpos;
      previous_ypos = ypos;
    }
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    calculate_camera(&camera, window, dt, previous_xpos, previous_ypos, xpos, ypos);
    previous_xpos = xpos;
    previous_ypos = ypos;
  } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE) {
    first_click = true;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  }
}

// For debugging our shapes
void toggle_wireframe_mode() {
  static bool draw_wireframe = true;
  if (draw_wireframe) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    draw_wireframe = false;
  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    draw_wireframe = true;
  }
}

// Some useful callbacks
void glfw_callbacks(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
  if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
    toggle_wireframe_mode();
  }
}

// Fix the camera when resizing the window
void glfw_window_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
  glm_perspective(camera.fov, (float)width/(float)height, camera.near, camera.far, camera.projection_matrix);
}

int main() {
  if (!glfwInit()) {
    printf("%s", "Error initializing GLFW\n");
    return 1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Should we use compat profile?
  GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Shader Guide", NULL, NULL);
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
  glfwSetKeyCallback(window, glfw_callbacks);
  glfwSetWindowSizeCallback(window, glfw_window_size_callback);

  // Setup our shapes
  Mesh plane = get_plane_vertices(100, 6);
  GLuint vao = ogl_generate_vertex_array();
  GLuint vbo = ogl_generate_buffer(sizeof(Vertex) * plane.vertex_count, plane.vertices);

  // Compile our shaders
  GLuint shader_id = ogl_compile_shader("shaders/color_fragment_shader.glsl", "shaders/color_vertex_shader.glsl", NULL);
  GLint projection_matrix_loc = ogl_get_uniform_location(shader_id, "projection_matrix");
  GLint view_matrix_loc = ogl_get_uniform_location(shader_id, "view_matrix");
  GLint model_matrix_loc = ogl_get_uniform_location(shader_id, "model_matrix");

  // Setup our camera
  camera = create_camera(45.0f, 0.1f, 1000.0f, (WINDOW_WIDTH / WINDOW_HEIGHT));
  calculate_camera(&camera, window, 0, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, WINDOW_WIDTH/1.05, WINDOW_HEIGHT/1.5);

  // The main loop
  while (!glfwWindowShouldClose(window)) {
    // Calculate simple delta-time
    static float lt = 0;
    float ct = glfwGetTime();
    float dt = ct - lt;
    lt = ct;

    // Clear the screen with our color
    ogl_clear(0.2f, 0.2f, 0.2f);

    // Calculate our new camera if we drag around in the viewport
    update_camera(window, dt);

    // We tell opengl to use our shader
    ogl_bind_shader(shader_id);

    // We bind our shape buffers
    ogl_bind_shape(vao, vbo);

    // Upload data to the shader inputs
    ogl_upload_mat4(projection_matrix_loc, camera.projection_matrix);
    ogl_upload_mat4(view_matrix_loc, camera.view_matrix);
    ogl_upload_mat4(model_matrix_loc, camera.model_matrix);

    // Draw
    ogl_draw_triangles(plane.vertex_count);

    // Poll events and swap buffers before new frame
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  return 0;
}
