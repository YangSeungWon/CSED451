#version 330 core
in vec3 fN;
in vec3 fE;
out vec4 fragcolor;

uniform float Shininess;
uniform vec4 AmbientProduct;
uniform vec4 DiffuseProduct;
uniform vec4 SpecularProduct;

uniform mat4 ModelView;
uniform mat4 View;
uniform mat4 Projection;
uniform vec4 DirectionalLightPosition;
uniform int LightNumber;
uniform vec4 PointLightList[10];

vec4 calculateLightColor(vec3 fL, float brightness, bool directional)
{
    vec3 N = normalize(fN);
    vec3 E = normalize(fE);
    vec3 L = normalize(fL);
    vec3 H = normalize(L + E);
	
    float Kd = max(dot(L, N), 0.0);
    vec4 diffuse = Kd * DiffuseProduct;
    float Ks = pow(max(dot(N, H), 0.0), Shininess);
    vec4 specular = Ks * SpecularProduct;
    if (dot(L, N) < 0.0)
    {
        specular = vec4(0.0, 0.0, 0.0, 1.0);
    }
    
    if (!directional)
    {
        float len = length(fE - fL) / 200;
        return (diffuse + specular) * min((1 / (0.5 + 1.0 * len + 2.0 * pow(len, 2))), 1);
    }
    else
    {
        return diffuse + specular;
    }
}

void main()
{
    vec4 ambient = AmbientProduct;
    fragcolor = ambient;
    
    vec3 fL;
    fL = (View * DirectionalLightPosition).xyz - fE;
    fragcolor += calculateLightColor(fL, 1.0, true);
    
    for (int i = 0; i < LightNumber; i++)
    {
        fL = (View * PointLightList[i]).xyz - fE;
        fragcolor += calculateLightColor(fL, 50.0, false);
    }
	fragcolor.a = 1.0;
}