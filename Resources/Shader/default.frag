#version 430 core
out vec4 FragColor;
in vec2 TexCoords;
in vec3 normal;
in vec3 curPos;
in mat3 TBN;

const int MAX_POINT_LIGHTS = 30;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 


struct PointLight{
	vec3 pos;
	vec3 direction;
	vec3 color;
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
uniform bool isParallaxMap;
uniform sampler2D normalMap0;
uniform sampler2D parallaxMap0;
uniform Material material;
uniform float heightScale;
uniform bool isDiffuseMap;
uniform vec2 textureOffset;
vec3 viewDirection;

vec3 pointLight(int i)
{
	vec3 lightDirection;

	vec3 normals;
	if (isNormalMap){
		normals = texture(normalMap0, TexCoords+textureOffset).rgb;
		normals = normalize(normals*2.0f - 1.0f);
		lightDirection = TBN*(gPointLights[i].pos-curPos);


	}

	else{
		normals = normal;
		lightDirection = gPointLights[i].pos-curPos;
	}

	vec3 ambientColor = vec3(gPointLights[i].intens)*material.ambient;

	float dist = length(lightDirection);
	lightDirection = normalize(lightDirection);
	float a = 1.8;
	float b = 0.7;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);
	
	float diffuse = max(dot(normals, lightDirection), 0.0f);
	
     vec3 DiffuseColor = ambientColor *  diffuse * material.diffuse;
	 
	
	vec3 reflectionDirection = reflect(-lightDirection, normals);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), material.shininess);
     vec3 specColor =  ambientColor * specAmount * material.specular   ;


	return ( DiffuseColor + specColor) * gPointLights[i].color *inten ;
}

vec3 directLight(int i){
	vec3 normals;
	vec3 lightDirection;
	if (isNormalMap){
		normals = texture(normalMap0, TexCoords+textureOffset).rgb;
		normals =  normalize(normals*2.0f - 1.0f);
		lightDirection = (normalize(TBN*(gPointLights[i].direction)));
	}
	else{
		normals = normal;
		lightDirection = (normalize((gPointLights[i].direction)));
	}
	vec3 ambientColor = vec3(gPointLights[i].intens)*material.ambient;


	
	float diffuse = max(dot(normals, lightDirection), 0.0f);
	
    vec3 DiffuseColor = ambientColor * diffuse *material.diffuse;

	vec3 reflectionDirection = reflect(-lightDirection, normals);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), material.shininess);
	vec3 specColor =  ambientColor * specAmount *material.specular;

	return (DiffuseColor + specColor) * gPointLights[i].color * gPointLights[i].intens  ;

}

vec3 spotLight(int i){
	vec3 normals;
	vec3 lightDirection;
	vec3 lightSelfDirection;

	if (isNormalMap){
		normals = texture(normalMap0, TexCoords+textureOffset).rgb;
		normals =  normalize(normals*2.0f - 1.0f);
		lightDirection = normalize(TBN*(gPointLights[i].pos - curPos));
		lightSelfDirection=normalize(-TBN*gPointLights[i].direction);
	}

	else{
		normals = normal;
		lightDirection = normalize(gPointLights[i].pos - curPos);
		lightSelfDirection=normalize(-gPointLights[i].direction);

	}
	float outerCone = 0.90f;
	float innerCone = 0.95f;

	

	vec3 ambientColor = vec3(gPointLights[i].intens)*material.ambient ;

	float diffuse = max(dot(normals, lightDirection), 0.0f);
	vec3 DiffuseColor = ambientColor  * diffuse*material.diffuse ;



	vec3 reflectionDirection = reflect(-lightDirection, normals);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), material.shininess);

	vec3 specColor =  ambientColor * specAmount*material.specular;

	
	float angle = dot(lightSelfDirection, lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);
	float dist = length(lightDirection);
	float a = 1.8;
	float b = 0.7;
	float aut = 1.0f / (a * dist * dist + b * dist + 1.0f);

	return (DiffuseColor + specColor) * gPointLights[i].color * aut * inten * gPointLights[i].intens  ;
}

 vec2 ParallaxMapping(vec2 texCoords1){ 
	const float numLayers = 100;

    float layerDepth = 1.0 / numLayers;

    float currentLayerDepth = 0.0;

    vec2 P = viewDirection.xy * heightScale; 
    vec2 deltaTexCoords = P / numLayers;



	vec2  currentTexCoords     = texCoords1;
	float currentDepthMapValue = texture(parallaxMap0, currentTexCoords).r;
  
	while(currentLayerDepth < currentDepthMapValue)
	{
		currentTexCoords -= deltaTexCoords;
		currentDepthMapValue = texture(parallaxMap0, currentTexCoords).r;  
		currentLayerDepth += layerDepth;  
	}

	vec2 prevTexCoords = currentTexCoords + deltaTexCoords;


	float afterDepth  = currentDepthMapValue - currentLayerDepth;
	float beforeDepth = texture(parallaxMap0, prevTexCoords).r - currentLayerDepth + layerDepth;
 
	float weight = afterDepth / (afterDepth - beforeDepth);
	vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

	return finalTexCoords;   
}

void main(){
	vec4 texColor= vec4(1.0f, 1.0f, 1.0f, 1.0f);
	if (isDiffuseMap){
		if (isParallaxMap){
			viewDirection = normalize(TBN*(camPos - curPos));

			vec2 texCoord2 = ParallaxMapping(TexCoords+textureOffset);

			texColor = texture(diffuse0, texCoord2);
	
		}
		else{
			texColor = texture(diffuse0, TexCoords+textureOffset);
		}

		if(texColor.a == 0.0f)
			discard;
	}
	if (isNormalMap){
		viewDirection = normalize(TBN*(camPos - curPos));
	}
	else{
		viewDirection = normalize(camPos - curPos);

	}



	vec4 totalLight = vec4(0.5f,0.5f,0.5f,1.0f);



	for (int i = 0; i < lightCount; i++){
		if (gPointLights[i].type == 0.0f){
			totalLight += vec4(pointLight(i), 0.0f);
		}
		else if (gPointLights[i].type == 1.0f){
			totalLight += vec4(directLight(i), 0.0f);

		}
		else if (gPointLights[i].type == 2.0f ){
			totalLight += vec4(spotLight(i), 0.0f);
		}
	}


	FragColor = texColor * color * (totalLight);
}