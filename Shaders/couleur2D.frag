#version 150 core

in vec3 color;
out vec4 out_Color;
uniform vec3 maCouleur;

void main()
{
    out_Color = vec4(maCouleur,1.0);
}
