#version 430 core
out vec4 FragColor;
in vec2 TexCoords;
in vec3 normal;
in vec3 curPos;
const int MAX_POINT_LIGHTS = 30;

struct PointLight{
	vec3 pos;
	vec3 direction;
	vec4 color;
	float intens;
	float type;
	bool isOn;
};

uniform sampler2D diffuse0;


uniform vec3 camPos;
uniform float lightCount;
uniform PointLight gPointLights[MAX_POINT_LIGHTS];
uniform vec4 color;
uniform bool isNormalMap;
uniform sampler2D normalMap0;


vec4 pointLight(int i)
{

	vec3 normals;
	if (isNormalMap){
		normals = texture(normalMap0, TexCoords).rgb;
		normals = normalize(normals*2.0f - 1.0f);
		//normal = normalize(rotation*normal);
	}
	else{
		normals = normal;
	}

	vec4 ambientColor = vec4(gPointLights[i].intens, gPointLights[i].intens, gPointLights[i].intens,1.0f) ;

	vec3 lightDirection = (gPointLights[i].pos-curPos);
	float dist = length(lightDirection);
	lightDirection = normalize(lightDirection);
	float a = 1.8;
	float b = 0.7;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);
	
	float diffuse = max(dot(normals, lightDirection), 0.0f);
	
     vec4 DiffuseColor = ambientColor *  diffuse;
	 
	
	vec3 viewDirection = normalize(camPos - curPos);
	vec3 reflectionDirection = reflect(-lightDirection, normals);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32);
     vec4 specColor =  ambientColor * specAmount   ;


	return ( DiffuseColor + specColor) * gPointLights[i].color *inten ;
}

vec4 directLight(int i){
	vec3 normals;
	if (isNormalMap){
		normals = texture(normalMap0, TexCoords).rgb;
		normals = normalize(normals*2.0f - 1.0f);
		//normal = normalize(rotation*normal);
	}
	else{
		normals = normal;
	}
	vec4 ambientColor = vec4(gPointLights[i].intens, gPointLights[i].intens, gPointLights[i].intens,1.0f) ;

	vec3 lightDirection = normalize(gPointLights[i].direction);

	
	float diffuse = max(dot(normals, lightDirection), 0.0f);
	
    vec4 DiffuseColor = ambientColor * diffuse ;

	vec3 viewDirection = normalize(camPos - curPos);
	vec3 reflectionDirection = reflect(-lightDirection, normals);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	vec4 specColor =  ambientColor * specAmount;

	return (DiffuseColor + specColor) * gPointLights[i].color * gPointLights[i].intens  ;

}

vec4 spotLight(int i){
	vec3 normals;
	if (isNormalMap){
		normals = texture(normalMap0, TexCoords).rgb;
		normals = normalize(normals*2.0f - 1.0f);
		//normal = normalize(rotation*normal);
	}
	else{
		normals = normal;
	}
	float outerCone = 0.90f;
	float innerCone = 0.95f;

	// ambient lighting
	

	vec4 ambientColor = vec4(gPointLights[i].intens, gPointLights[i].intens, gPointLights[i].intens,1.0f) ;

	// diffuse lighting
	vec3 lightDirection = normalize(gPointLights[i].pos - curPos);
	float diffuse = max(dot(normals, lightDirection), 0.0f);
	vec4 DiffuseColor = ambientColor  * diffuse ;


	// specular lighting

	vec3 viewDirection = normalize(camPos - curPos);
	vec3 reflectionDirection = reflect(-lightDirection, normals);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 32);

	vec4 specColor =  ambientColor * specAmount;

	
	float angle = dot(normalize(-gPointLights[i].direction), lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);
	float dist = length(lightDirection);
	float a = 1.8;
	float b = 0.7;
	float aut = 1.0f / (a * dist * dist + b * dist + 1.0f);

	return (DiffuseColor + specColor) * gPointLights[i].color * aut * inten * gPointLights[i].intens  ;
}

void main()
{
	
	bool tmp1 = false;
	vec4 totalLight = vec4(0.5f,0.5f,0.5f,1.0f);



	for (int i = 0; i < lightCount; i++){
		if (gPointLights[i].type == 0.0f && gPointLights[i].isOn){
			totalLight += pointLight(i);
		}
		else if (gPointLights[i].type == 1.0f && gPointLights[i].isOn){
			totalLight += directLight(i);

		}
		else if (gPointLights[i].type == 2.0f && gPointLights[i].isOn){
			totalLight += spotLight(i);
		}
	}
	FragColor = texture(diffuse0, TexCoords) * (totalLight);

}