#version 150 core

in vec2 coordTexture;

uniform sampler2D tex;
uniform vec3 ambiantLightColor;
uniform float ambiantIntensity;


out vec4 out_Color;

void main()
{
    out_Color = texture(tex, coordTexture)*vec4(ambiantLightColor,1.0)*ambiantIntensity;
	if(out_Color.a == 0)
	{
		discard;
	}
}
