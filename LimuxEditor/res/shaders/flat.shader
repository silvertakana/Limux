#shader vertex
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in vec4 a_Color;
out vec4 v_Color;
out vec2 v_TexCoord;
uniform mat4 u_CamMatrix;
uniform mat4 u_Transform;
void main()
{
	v_Color = a_Color;
	v_TexCoord =  a_TexCoord;
	gl_Position = u_CamMatrix * u_Transform * vec4(a_Position, 1.0);
}
#shader fragment
layout(location = 0) out vec4 color;
in vec4 v_Color;
in vec2 v_TexCoord;
uniform sampler2D u_Texture_Diffuse0;
void main()
{
	color = texture(u_Texture_Diffuse0, v_TexCoord);
	//if(color.a < 0.5f)
	//	discard;
}