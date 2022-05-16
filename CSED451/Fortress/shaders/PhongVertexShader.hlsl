#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 2) in vec3 vNormal;
out vec3 fN;
out vec3 fE;
out vec3 fL;

uniform mat4 ModelView;
uniform mat4 Projection;
uniform vec4 LightPosition;

void main()
{
	vec4 vPosition = ModelView * vec4(vPos, 1.0);
	
    fN = (ModelView * vec4(vNormal, 0.0)).xyz;
    fE = -vPosition.xyz;
	fL = LightPosition.xyz;
	
	if (LightPosition.w != 0.0)
	{
		fL = LightPosition.xyz - vPosition.xyz;
    }
    gl_Position = Projection * vPosition / vPosition.w;
}