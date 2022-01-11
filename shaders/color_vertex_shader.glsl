#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 view_matrix;
uniform mat4 projection_matrix;
uniform mat4 model_matrix;

out vec3 fs_normal;
out vec2 fs_uv;

void main() {
    fs_normal = normal;
    fs_uv = uv;
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(position, 1.0);
}
