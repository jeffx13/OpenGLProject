#version 450 core
#define MAXDIRLIGHTS 10
#define MAXPOINTLIGHTS 10
#define MAXSPOTLIGHTS 10
layout(location = 0) out vec4 FragColor;

struct Dirlight{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 colour;
};

struct Pointlight{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 colour;
};

struct Spotlight{
    vec3 position;
    vec3 direction;
    float innerCutOff;
    float outerCutOff;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 colour;
};

layout (std140,binding = 1) uniform dirLightBlock
{
    Dirlight dirlights[MAXDIRLIGHTS];
};

layout (std140,binding = 2) uniform pointLightBlock
{
    Pointlight pointlights[MAXPOINTLIGHTS];
};

layout (std140,binding = 3) uniform spotLightBlock
{
    Spotlight spotlights[MAXSPOTLIGHTS];
};

in VS_OUT {
    vec3 FragPos;
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



uniform Dirlight dirlight;
uniform Pointlight pointlight;
uniform Spotlight spotlight;

uniform vec3 viewPos;

uniform sampler2D normal0;
uniform sampler2D normal1;
uniform sampler2D diffuse0;
uniform sampler2D diffuse1;
uniform sampler2D specular0;
uniform sampler2D specular1;

vec3 calcDirLight(vec3 norm, vec3 viewDir, vec3 diffMap, vec3 specMap);
vec3 calcPointLight(int idx, vec3 norm, vec3 viewDir, vec3 diffMap, vec3 specMap);
vec3 calcSpotLight(int idx, vec3 norm, vec3 viewDir, vec3 diffMap, vec3 specMap);

void main()
{
    vec3 normal = texture(normal0, fs_in.TexCoords).rgb;
	normal = normalize(normal * 2.0 - 1.0);
    vec3 diffMap = texture(diffuse0,fs_in.TexCoords).xyz;
    vec3 specMap = texture(specular0,fs_in.TexCoords).xyz;
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);

    //vec3 point = vec3(0.0f,0.0f,0.0f);
    //for(int i=0;i<int(MAXPOINTLIGHTS);++i){point += calcPointLight(i,normal,viewDir,diffMap,specMap);}
    
    vec3 point = calcPointLight(1,normal,viewDir,diffMap,specMap);
    FragColor = vec4(point,1.0f);
};

vec3 calcPointLight(int idx, vec3 norm, vec3 viewDir, vec3 diffMap, vec3 specMap){

    vec3 ambient = 0.5* pointlight.ambient * diffMap;
    
    //diffuse
    vec3 lightDir = normalize(pointlight.position - fs_in.FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = pointlight.diffuse * (diff * diffMap);

    //specular
    vec3 reflectDir = reflect(-lightDir, norm);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(norm, reflectDir ), 0.0), 0.5*128);
    vec3 specular = pointlight.specular * spec * specMap;

    return (ambient+diffuse+specular);
}

vec3 calcDirLight(vec3 norm, vec3 viewDir, vec3 diffMap, vec3 specMap){
    vec3 ambient = dirlight.ambient * diffMap;
    
    //diffuse
    
    float diff = max(dot(norm, dirlight.direction), 0.0);
    vec3 diffuse = dirlight.diffuse * (diff * diffMap);

    //specular
    vec3 reflectDir = reflect(-dirlight.direction, norm);
    vec3 halfwayDir = normalize(dirlight.direction + viewDir);  
    float spec = pow(max(dot(norm, reflectDir ), 0.0), 0.5*128);
    vec3 specular = dirlight.specular * spec * specMap;

    return (ambient+diffuse+specular);
}

vec3 calcSpotLight(int idx, vec3 norm, vec3 viewDir, vec3 diffMap, vec3 specMap){

    vec3 ambient = spotlight.ambient * diffMap; 
    vec3 lightDir = normalize(spotlight.position - fs_in.FragPos);
    float theta = dot(lightDir, spotlight.direction);

    if (theta > spotlight.outerCutOff) {
		// diffuse
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = spotlight.diffuse * (diff * diffMap);

		// specular
        float dotProd = 0.0;
		vec3 halfwayDir = normalize(lightDir + viewDir);
		dotProd = dot(norm, halfwayDir);
		vec3 reflectDir = reflect(-spotlight.direction, norm);
        float spec = pow(max(dot(norm, reflectDir ), 0.0), 0.5*128);
        vec3 specular = spotlight.specular * spec * specMap;
		float intensity = clamp((theta - spotlight.outerCutOff) / (spotlight.innerCutOff - spotlight.outerCutOff), 0.0, 1.0);
	    diffuse *= intensity;
	    specular *= intensity;
        return (ambient+diffuse+specular);
    }
    else{
        return ambient;
        }
}
