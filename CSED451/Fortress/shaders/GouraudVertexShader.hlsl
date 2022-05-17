#version 330 core
layout(location = 0) in vec3 vPos;
layout(location = 1) in vec2 vUv;
layout(location = 2) in vec3 vNormal;
out vec4 color;
out vec2 texCoord;

uniform mat4 ModelView;
uniform mat4 View;
uniform mat4 Projection;
uniform vec4 DirectionalLightPosition;
uniform int LightNumber;
uniform vec4 PointLightList[10];
uniform float Shininess;
uniform vec4 AmbientProduct;
uniform vec4 DiffuseProduct;
uniform vec4 SpecularProduct;

vec4 calculateLightColor(vec3 pos, vec4 lightPosition, float brightness)
{
    vec3 L;
    if (lightPosition.w != 0.0)
    {
        L = normalize(lightPosition.xyz - pos);
    }
    else
    {
        L = normalize(lightPosition.xyz);
    }
		
    vec3 E = normalize(-pos);
    vec3 H = normalize(L + E);
	
    vec3 N = normalize(ModelView * vec4(vNormal, (0.0))).xyz;
	
    float Kd = max(dot(L, N), 0.0);
    vec4 diffuse = Kd * DiffuseProduct;
    float Ks = pow(max(dot(N, H), 0.0), Shininess * brightness);
    vec4 specular = Ks * SpecularProduct;
    if (dot(L, N) < 0.0)
    {
        specular = vec4(0.0, 0.0, 0.0, 1.0);
    }
    
    if (lightPosition.w != 0.0)
    {
        float len = length(pos - lightPosition.xyz) / 200;
        return (diffuse + specular) * min((1 / (0.5 + 1.0 * len + 2.0 * pow(len, 2))), 1);
    }
    else
    {
        return diffuse + specular;
    }
}

void main()
{
	vec4 vPosition = vec4(vPos, 1.0);
	gl_Position = Projection * ModelView * vPosition / vPosition.w;

	vec3 pos = (ModelView * vPosition).xyz;
	
    vec4 ambient = AmbientProduct;
    
	color = ambient;
    color += calculateLightColor(pos, View * DirectionalLightPosition, 1.0);
    
    for (int i = 0; i < LightNumber; i++)
    {
        color += calculateLightColor(pos, View * PointLightList[i], 50.0);
    }
    color.a = 1.0;
    texCoord = vUv;
}
