#version 450 core
#define MAXDIRLIGHTS 10
#define MAXPOINTLIGHTS 10
#define MAXSPOTLIGHTS 10
layout(location = 0) out vec4 FragColor;

struct Dirlight{
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    vec3 colour;

    vec3 direction;
    };

struct Pointlight{
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    vec3 colour;

    vec3 position;
    };

struct Spotlight{
    vec3 diffuse;
	vec3 ambient;
	vec3 specular;
	vec3 colour;

	vec3 position;
	vec3 direction;
	float innerCutOff;
	float outerCutOff;
    };

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform vec3 viewPos;
uniform int b_normal_map;
uniform sampler2D normal0;
uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform Pointlight pointlights[MAXPOINTLIGHTS];
uniform Dirlight dirlights[MAXDIRLIGHTS];
uniform Spotlight spotlights[MAXSPOTLIGHTS];


vec3 calcDirLight(int idx,vec3 norm, vec3 viewDir, vec3 diffMap, vec3 specMap);

vec3 calcPointLight(int idx, vec3 norm, vec3 viewDir, vec4 diffMap, vec4 specMap);

vec3 calcSpotLight(int idx, vec3 norm, vec3 viewDir, vec3 diffMap, vec3 specMap);

void main()
{
    vec3 normal = normalize(texture(normal0, fs_in.TexCoords).xyz);
    if(b_normal_map<0){
    normal = fs_in.Normal;
    }
	
    vec4 diffMap = texture(diffuse0,fs_in.TexCoords);
    vec4 specMap = texture(specular0,fs_in.TexCoords);
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);

    vec3 point = vec3(0.0f,0.0f,0.0f);
    for(int i=0;i<int(MAXPOINTLIGHTS);++i){point += calcPointLight(i,normal,viewDir,diffMap,specMap);}

    FragColor = vec4(point,1.0f);
};
vec3 calcPointLight(int idx, vec3 norm, vec3 viewDir, vec4 diffMap, vec4 specMap){

   vec4 ambient = vec4(pointlights[idx].ambient,1.0f) * diffMap;

	vec3 lightDir = normalize(pointlights[idx].position - fs_in.FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec4 diffuse = vec4(pointlights[idx].diffuse,1.0f) * (diff * diffMap);

	vec4 specular = vec4(0.0, 0.0, 0.0, 1.0);
	if (diff > 0) {
		float dotProd = 0.0;

		vec3 halfwayDir = normalize(lightDir + viewDir);
		dotProd = dot(norm, halfwayDir);

		float spec = pow(max(dotProd, 0.0), 16);
		specular = vec4(pointlights[idx].specular,1.0f) * (spec * specMap);
	}
	float dist = length(pointlights[idx].position - fs_in.FragPos);
    float a = 1.00f;
	float b = 0.70f;
	float attenuation = 1.0 / (1.0f + a * dist + b * (dist * dist));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return vec4(ambient + (diffuse + specular)).xyz * pointlights[idx].colour;
}

vec3 calcSpotLight(int idx, vec3 norm, vec3 viewDir, vec3 diffMap, vec3 specMap){

    vec3 ambient = spotlights[idx].ambient * diffMap; 
    vec3 lightDir = normalize(spotlights[idx].position - fs_in.FragPos);
    float theta = dot(lightDir, spotlights[idx].direction);

    if (theta > spotlights[idx].outerCutOff) {
		// diffuse
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = spotlights[idx].diffuse * (diff * diffMap);

		// specular
        float dotProd = 0.0;
		vec3 halfwayDir = normalize(lightDir + viewDir);
		dotProd = dot(norm, halfwayDir);
		vec3 reflectDir = reflect(-spotlights[idx].direction, norm);
        float spec = pow(max(dot(norm, reflectDir ), 0.0), 0.5*128);
        vec3 specular = spotlights[idx].specular * spec * specMap;
		float intensity = clamp((theta - spotlights[idx].outerCutOff) / (spotlights[idx].innerCutOff - spotlights[idx].outerCutOff), 0.0, 1.0);
	    diffuse *= intensity;
	    specular *= intensity;
        return (ambient+diffuse+specular);
    }
    else{
        return ambient;
        }
}
