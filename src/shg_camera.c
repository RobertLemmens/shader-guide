/**
 * @file shg_camera.h
 * @author Robert Lemmens
 * @date 11-1-2022
 * @brief shg_camera module.
 *
 * Description
 */
#include "shg_camera.h"
void calculate_camera(Camera *camera, GLFWwindow *window, float dt,double initial_x_position, double initial_y_position, double xpos, double ypos) {
  camera->horizontal_angle += 0.005f * (initial_x_position - xpos );
  camera->vertical_angle   += 0.005f * (initial_y_position - ypos );

  // Direction : Spherical coordinates to Cartesian coordinates conversion
  vec3 direction = {
      cos(camera->vertical_angle) * sin(camera->horizontal_angle),
      sin(camera->vertical_angle),
      cos(camera->vertical_angle) * cos(camera->horizontal_angle)
  };

  vec3 right = {
      sin(camera->horizontal_angle - 3.14f / 2.0f),
      0,
      cos(camera->horizontal_angle - 3.14f / 2.0f)
  };

  vec3 cross;
  glm_vec3_cross(right, direction, cross);
  float speed = 10.0f;

  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    speed = 30.0f;
  }

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    vec3 temp;
    glm_vec3_scale(direction, dt * speed, temp);
    glm_vec3_add(camera->position, temp, camera->position);
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    vec3 temp;
    glm_vec3_scale(direction, dt * speed, temp);
    glm_vec3_sub(camera->position, temp, camera->position);
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    vec3 temp;
    glm_vec3_scale(right, dt * speed, temp);
    glm_vec3_add(camera->position, temp, camera->position);
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    vec3 temp;
    glm_vec3_scale(right, dt * speed, temp);
    glm_vec3_sub(camera->position, temp, camera->position);
  }

  mat4 view;
  vec3 tmp;
  glm_vec3_add(camera->position, direction, tmp);
  glm_lookat(camera->position, tmp, cross, view);
  glm_mat4_copy(view, camera->view_matrix);
  glm_mat4_mulN((mat4 *[]){&camera->projection_matrix, &camera->view_matrix, &camera->model_matrix}, 3, camera->mvp);
}

Camera create_camera(float fov, float near, float far, float aspect) {
  mat4 model;
  glm_mat4_identity(model);

  mat4 view;
  vec3 eye = {-4, 4, -4};
  vec3 center = {0, 0, 0};
  vec3 up = {0, 1 , 0};
  glm_lookat(eye, center, up, view);

  mat4 projection;
  glm_perspective(fov, aspect, near, far, projection);

  glm_scale(model, (vec3){1,1,1});

  mat4 mvp;
  glm_mat4_mulN((mat4 *[]){&projection, &view, &model}, 3, mvp);

  Camera camera;
  glm_mat4_copy(mvp, camera.mvp);
  glm_mat4_copy(view, camera.view_matrix);
  glm_mat4_copy(projection, camera.projection_matrix);
  glm_mat4_copy(model, camera.model_matrix);
  glm_vec3_copy(eye, camera.position);
  camera.fov = fov;
  camera.near = near;
  camera.far = far;
  camera.aspect = aspect;
  camera.horizontal_angle = 3.14f;
  camera.vertical_angle = 0.0f;

  return camera;
}
