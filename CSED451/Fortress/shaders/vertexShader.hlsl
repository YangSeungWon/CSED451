#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 2) in vec3 vNormal;
out vec4 color;

uniform mat4 ModelView;
uniform mat4 Projection;
uniform vec4 LightPosition;
uniform float Shininess;
uniform vec4 AmbientProduct;
uniform vec4 DiffuseProduct;
uniform vec4 SpecularProduct;

void main()
{
	vec4 vPosition = vec4(vPos, 1.0);
	gl_Position = Projection * ModelView * vPosition / vPosition.w;

	vec3 pos = (ModelView * vPosition).xyz;
	vec3 L = normalize(LightPosition.xyz - pos);
	vec3 E = normalize(-pos);
	vec3 H = normalize(L + E);
	
	vec3 N = normalize(ModelView * vec4(vNormal, (0.0))).xyz;
	
	vec4 ambient = AmbientProduct;
	float Kd = max(dot(L, N), 0.0);
	vec4 diffuse = Kd * DiffuseProduct;
	float Ks = pow(max(dot(N, H), 0.0), Shininess);
	vec4 specular = Ks * SpecularProduct;
	if (dot(L, N) < 0.0)
	{
		specular = vec4(0.0, 0.0, 0.0, 1.0);
	}
	color = ambient + diffuse + specular;
	color.a = 1.0;
}