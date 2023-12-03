#version 410 core
out vec4 frag_color;
uniform vec4 color;
uniform vec4 light;
void main(void)
{
    frag_color = light*color ;
}
