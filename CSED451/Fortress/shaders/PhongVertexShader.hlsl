#version 330 core
layout (location = 0) in vec3 vPos;
layout(location = 1) in vec2 vUv;
layout (location = 2) in vec3 vNormal;
out vec3 fN;
out vec3 fE;
out vec2 texCoord;

uniform mat4 ModelView;
uniform mat4 Projection;
uniform vec4 DirectionalLightPosition;
uniform int LightNumber;
uniform vec4 PointLightList[10];

void main()
{
	vec4 vPosition = ModelView * vec4(vPos, 1.0);
	
    fN = (ModelView * vec4(vNormal, 0.0)).xyz;
    fE = vPosition.xyz;
    
    gl_Position = Projection * vPosition / vPosition.w;
    texCoord = vUv;
}