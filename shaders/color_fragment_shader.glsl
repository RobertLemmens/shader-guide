#version 330 core

in vec3 fs_normal;
in vec2 fs_uv;

out vec4 fragment_color;

void main() {
    fragment_color = vec4(1.0, 0.0, 1.0, 1.0);
}
