#version 150 core

in vec3 in_Vertex;
in vec2 in_TexCoord0;
in vec3 in_Normals;

uniform mat4 projection;
uniform mat4 modelview;

out vec2 coordTexture;

void main()
{
    gl_Position = projection*modelview* vec4(in_Vertex,1.0);

    coordTexture = in_TexCoord0;
}
