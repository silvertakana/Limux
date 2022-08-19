#shader vertex
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in vec4 a_Color;
out vec4 v_Color;
out vec3 v_Normal;
out vec2 v_TexCoord;
out vec3 v_FragPos;
uniform mat4 u_CamMatrix;
uniform mat4 u_Transform;
void main()
{
	v_FragPos = vec3(u_Transform * vec4(a_Position, 1.0));
	gl_Position = u_CamMatrix * vec4(v_FragPos, 1.0);
	
	v_Color = a_Color;
	v_Normal = normalize(mat3(transpose(inverse(u_Transform))) * a_Normal);
	v_TexCoord = a_TexCoord;
}
#shader fragment

layout(location = 0) out vec4 PixelColor;
in vec4 v_Color;
in vec3 v_Normal;
in vec2 v_TexCoord;
in vec3 v_FragPos;

uniform sampler2D u_Texture_Diffuse[16];
uniform sampler2D u_Texture_Specular[16];
uniform sampler2D u_Texture_Ambient[16];

struct Camera
{
	vec3 Position;
	vec3 Front;
	vec3 Up;
};

uniform Camera u_Camera;

struct Light
{
	vec3 Position;
	vec3 Front;
	vec3 Color;
	float Intensity;
	bool Enabled;
	int  Type;
};
#define LIGHT_COUNT 20
uniform Light u_Lights[LIGHT_COUNT];

vec3 AmbientLightColor = vec3(0.3, 0.3, 0.6);
void main()
{
	vec3 viewDir = normalize(u_Camera.Position - v_FragPos); 
	float flipNormal = dot(viewDir, v_Normal);
	vec3 Normal = v_Normal * flipNormal/abs(flipNormal);
	
	
	float ambientStrength = 0.8;
	vec3 ambient = ambientStrength * AmbientLightColor;
	
	vec4 baseColor = texture(u_Texture_Diffuse[0], v_TexCoord);
	vec3 diffuse = vec3(0.f);
	vec3 specular = vec3(0.f);
	for (int i = 0; i < LIGHT_COUNT; i++) {
		if (u_Lights[i].Enabled)
		{
			vec3 lightDir = normalize(u_Lights[i].Position - v_FragPos);
			float diff = max(dot(Normal, lightDir), 0.0);
			diffuse += diff * u_Lights[i].Color * u_Lights[i].Intensity;

			vec3 reflectDir = reflect(-lightDir, Normal);
			float spec = pow(max(dot(viewDir, reflectDir), 0.0), (1.f - texture(u_Texture_Specular[0], v_TexCoord).r) * 32.f);
			specular += spec * u_Lights[i].Color * u_Lights[i].Intensity;
		}
	}
	
	PixelColor = vec4(ambient + diffuse + specular , 1.f) * baseColor;
	//PixelColor = vec4(Normal, 1.f);
	if(PixelColor.a < 0.5f)
		discard;
}