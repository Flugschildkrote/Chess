#version 330 core

in vec3 in_Vertex;
in vec2 in_TexCoord0;
in vec3 in_Normals;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 modelviewProjection;
uniform mat4 normalsMatrix;

out vec2 coordTexture;
out vec3 vertexNormal;

void main()
{
    gl_Position = modelviewProjection* vec4(in_Vertex,1.0);

    coordTexture = in_TexCoord0;
	vec4 normal = normalsMatrix*vec4(in_Normals,0.0);
	//vec4 normal = vec4(in_Normals,0.0);
	vertexNormal = normal.xyz;
	//vertexNormal = in_Normals;
}
