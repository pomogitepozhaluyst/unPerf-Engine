#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 matPV;
uniform mat3 rotation;

uniform vec3 translate;
uniform vec3 scale;



out vec3 curPos;


out vec3 color;
out vec3 normal;
out vec2 TexCoords;

vec3 TRS(vec3 v){
	vec3 tmp = rotation * vec3(v.x*scale.x,v.y*scale.y, v.z*scale.z);
	return vec3(tmp.x+translate.x, tmp.y+translate.y, tmp.z+translate.z);
}

void main()
{
	curPos = TRS(aPos);
	normal = normalize(rotation*aNorm);

	TexCoords = aTexCoords;
	gl_Position = matPV * vec4(curPos, 1.0);	
}