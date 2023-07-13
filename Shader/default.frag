#version 430 core
out vec4 FragColor;
in vec2 TexCoords;
in vec3 normal;
in vec3 curPos;
in mat3 TBN;
in mat3 rotation1;

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
vec3 viewDirection;

vec3 pointLight(int i)
{

	vec3 normals;
	if (isNormalMap){
		normals = texture(normalMap0, TexCoords).rgb;
		normals = normalize(normals*2.0f - 1.0f);
	}
	else{
		normals = normal;
	}

	vec3 ambientColor = vec3(gPointLights[i].intens)*material.ambient;

	vec3 lightDirection = TBN*(gPointLights[i].pos-curPos);
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
	if (isNormalMap){
		normals = texture(normalMap0, TexCoords).rgb;
		normals = normalize(normals*2.0f - 1.0f);
	}
	else{
		normals = normal;
	}
	vec3 ambientColor = vec3(gPointLights[i].intens)*material.ambient;

	vec3 lightDirection = (normalize(TBN*(gPointLights[i].direction)));

	
	float diffuse = max(dot(normals, lightDirection), 0.0f);
	
    vec3 DiffuseColor = ambientColor * diffuse *material.diffuse;

	vec3 reflectionDirection = reflect(-lightDirection, normals);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), material.shininess);
	vec3 specColor =  ambientColor * specAmount *material.specular;

	return (DiffuseColor + specColor) * gPointLights[i].color * gPointLights[i].intens  ;

}

vec3 spotLight(int i){
	vec3 normals;
	if (isNormalMap){
		normals = texture(normalMap0, TexCoords).rgb;
		normals =  normalize(normals*2.0f - 1.0f);
	}

	else{
		normals = normal;
	}
	float outerCone = 0.90f;
	float innerCone = 0.95f;

	// ambient lighting
	

	vec3 ambientColor = vec3(gPointLights[i].intens)*material.ambient ;

	// diffuse lighting
	vec3 lightDirection = normalize(TBN*(gPointLights[i].pos - curPos));
	float diffuse = max(dot(normals, lightDirection), 0.0f);
	vec3 DiffuseColor = ambientColor  * diffuse*material.diffuse ;


	// specular lighting

	vec3 reflectionDirection = reflect(-lightDirection, normals);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), material.shininess);

	vec3 specColor =  ambientColor * specAmount*material.specular;

	
	float angle = dot(normalize(-TBN*gPointLights[i].direction), lightDirection);
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
		// смещаем текстурные координаты вдоль вектора P
		currentTexCoords -= deltaTexCoords;
		// делаем выборку из карты глубин в текущих текстурных координатах 
		currentDepthMapValue = texture(parallaxMap0, currentTexCoords).r;  
		// рассчитываем глубину следующего слоя
		currentLayerDepth += layerDepth;  
	}

	vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

	// находим значения глубин до и после нахождения пересечения 
	// для использования в линейной интерполяции
	float afterDepth  = currentDepthMapValue - currentLayerDepth;
	float beforeDepth = texture(parallaxMap0, prevTexCoords).r - currentLayerDepth + layerDepth;
 
	// интерполяция текстурных координат 
	float weight = afterDepth / (afterDepth - beforeDepth);
	vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

	return finalTexCoords;   
}

void main(){
	vec4 texColor= vec4(1.0f, 1.0f, 1.0f, 1.0f);
	viewDirection = normalize(TBN*(camPos - curPos));
	if (isDiffuseMap){
		if (isParallaxMap){
			vec2 texCoord2 = ParallaxMapping(TexCoords);

			texColor = texture(diffuse0, texCoord2);
	
		}
		else{
			texColor = texture(diffuse0, TexCoords);
		}

		if(texColor.a == 0.0f)
			discard;
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