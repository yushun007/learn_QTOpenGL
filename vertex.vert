#version 410 core
layout (location = 0) in vec3 position;
uniform mat4 projection_mat;
uniform mat4 mv_mat;
void main() {
    gl_Position = projection_mat * mv_mat * vec4(position, 1.f);
}
