#version 410 core
layout (location = 0) in vec3 position;
uniform mat4 projection_mat;
uniform mat4 view_mat;
uniform mat4 model_mat;
uniform vec4 color;
void main() {
    gl_Position = projection_mat * view_mat*model_mat* vec4(position, 1.f);
}
