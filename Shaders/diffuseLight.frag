#version 330 core

in vec2 coordTexture;
in vec3 vertexNormal;
out vec4 out_Color;

uniform sampler2D tex;

struct directionnalLight
{
	float ambiantIntensity;
	vec3 direction;
	vec3 color;
};

uniform directionnalLight sun;
uniform float modelIntensity;

void main()
{
	vec4 textureColor = texture(tex, coordTexture);
	float diffuseIntensity = max(0.0, dot(normalize(vertexNormal),-sun.direction));
    out_Color = textureColor * vec4(modelIntensity,modelIntensity,modelIntensity,1.0) * vec4(sun.color *(sun.ambiantIntensity+diffuseIntensity),1.0);
	if(out_Color.a == 0)
	{
		discard;
	}
}