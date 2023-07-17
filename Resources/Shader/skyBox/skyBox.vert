#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 matPV;
uniform vec3 scale;

uniform vec3 translate;

vec3 TRS(vec3 v){
	vec3 tmp =  vec3(v.x*scale.x,v.y*scale.y, v.z*scale.z);
	return vec3(tmp.x+translate.x, tmp.y+translate.y, tmp.z+translate.z);
}
void main()
{
    TexCoords = aPos;
    gl_Position = matPV *vec4(TRS(aPos), 1.0f);
}