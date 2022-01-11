/**
 * @file shg_camera.h
 * @author Robert Lemmens
 * @date 11-1-2022
 * @brief shg_camera module.
 *
 * Description
 */
#ifndef SHADER_GUIDE_SHG_CAMERA_H
#define SHADER_GUIDE_SHG_CAMERA_H
#include "GLFW/glfw3.h"
#include "cglm/cglm.h"

typedef struct Camera_s {
  mat4 mvp;
  mat4 view_matrix;
  mat4 projection_matrix;
  mat4 model_matrix;
  vec3 position;
  float horizontal_angle;
  float vertical_angle;
  float fov;
  float near;
  float far;
  float aspect;
} Camera;

Camera create_camera(float fov, float near, float far, float aspect);
void calculate_camera(Camera *camera, GLFWwindow *window,float dt,double initial_x_position, double initial_y_position, double xpos, double ypos);
#endif //SHADER_GUIDE_SHG_CAMERA_H
