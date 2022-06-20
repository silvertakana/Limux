#shader vertex
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in vec4 a_Color;

out vec3 v_Normal;
out vec2 v_TexCoord;
out vec4 v_Color;

uniform mat4 u_CamMatrix;
uniform mat4 u_Transform;
uniform vec2 tiling;

void main()
{
	v_Normal = a_Normal;
	v_TexCoord = a_TexCoord * tiling;
	v_Color = a_Color;
	gl_Position = u_CamMatrix * u_Transform * vec4(a_Position, 1.0);
}
#shader fragment
layout(location = 0) out vec4 color;
in vec3 v_Normal;
in vec2 v_TexCoord;
in vec4 v_Color;
uniform sampler2D u_Texture_Diffuse0;

vec3 tonemapFilmic(vec3 x)
{
	vec3 X = max(vec3(0.0), x - 0.004);
	vec3 result = (X * (6.2 * X + 0.5)) / (X * (6.2 * X + 1.7) + 0.06);
	return pow(result, vec3(2.2));
}

float tonemapFilmic(float x)
{
	float X = max(0.0, x - 0.004);
	float result = (X * (6.2 * X + 0.5)) / (X * (6.2 * X + 1.7) + 0.06);
	return pow(result, 2.2);
}

void main()
{
	color = vec4(v_Normal, 1.f);
	if (color.a < 0.5f)
		discard;
}