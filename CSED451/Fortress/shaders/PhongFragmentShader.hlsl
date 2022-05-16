#version 330 core
in vec3 fN;
in vec3 fE;
in vec3 fL;
out vec4 fragcolor;

uniform float Shininess;
uniform vec4 AmbientProduct;
uniform vec4 DiffuseProduct;
uniform vec4 SpecularProduct;

uniform mat4 ModelView;
uniform mat4 Projection;
uniform vec4 LightPosition;

void main()
{
	vec3 N = normalize(fN);
	vec3 E = normalize(fE);
	vec3 L = normalize(fL);
	
	vec3 H = normalize(L + E);
	vec4 ambient = AmbientProduct;
	
	float Kd = max(dot(L, N), 0.0);
	vec4 diffuse = Kd * DiffuseProduct;
	float Ks = pow(max(dot(N, H), 0.0), Shininess);
	vec4 specular = Ks * SpecularProduct;
	if (dot(L, N) < 0.0)
	{
		specular = vec4(0.0, 0.0, 0.0, 1.0);
	}
	fragcolor = ambient + diffuse + specular;
	fragcolor.a = 1.0;

}