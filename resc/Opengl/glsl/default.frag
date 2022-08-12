#version 430 core
struct PointLight{
    vec3 lightPos;
    vec3 lightColor;

    vec3 lightAmbient;
    vec3 lightDiffuse;
    vec3 lightSpecular;

    float lightConstant;
    float lightLinear;
    float lightQuadratic;
};
struct DirLight{
    vec3 lightColor;
    vec3 lightDir;

    vec3 lightAmbient;
    vec3 lightDiffuse;
    vec3 lightSpecular;
};
struct SpotLight{
    vec3 lightPos;
    vec3 lightColor;

    vec3 lightAmbient;
    vec3 lightDiffuse;
    vec3 lightSpecular;
    vec3 lightDir;
    float lightInnerCutOff;
    float lightOuterCutOff;
    float lightConstant;
    float lightLinear;
    float lightQuadratic;
};
out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;
in vec3 objectColor;
uniform PointLight pointLight[5];
uniform DirLight   dirLight[5];
uniform SpotLight  spotLight[5];
uniform vec3  viewPos;
uniform vec3  materialAmbient;
uniform vec3  materialDiffuse;
uniform vec3  materialSpecluar;
uniform float materialShininess;

uniform int pointLightNum;
uniform int dirLightNum;
uniform int spotLightNum;
uniform bool isUseLight;
uniform bool isPointLightAttenuation;
uniform bool isSpotLightAttenuation;

vec3 calPointLight(PointLight light);
vec3 calDirLight(DirLight light);
vec3 calSpotLight(SpotLight light);
void main()
{
    vec3 result = vec3(0.0f, 0.0f, 0.0f);
    if(isUseLight){
       for(int i = 0; i < pointLightNum; i++){
           result += calPointLight(pointLight[i]);
       }
       for(int i = 0; i < dirLightNum; i++){
           result += calDirLight(dirLight[i]);
       }
           for(int i = 0; i < spotLightNum; i++){
           result += calSpotLight(spotLight[i]);
       }
    }else{
        result = vec3(objectColor);
    }
    FragColor = vec4(result, 1.0);
}

vec3 calPointLight(PointLight light){
    vec3 ambient = light.lightColor * materialAmbient;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.lightColor * (diff * materialDiffuse);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininess);
    vec3 specular = light.lightColor * (spec * materialSpecluar);

    ambient  *= light.lightAmbient;
    specular *= light.lightSpecular;
    diffuse  *= light.lightDiffuse;
        if(isPointLightAttenuation){
                float distance    = length(light.lightPos - FragPos);
                float attenuation = 1.0 / (light.lightConstant + light.lightLinear * distance + light.lightQuadratic * (distance * distance));
                ambient  *= attenuation;
            specular *= attenuation;
                diffuse *= attenuation;
        }
        vec3 result = (ambient + diffuse + specular);
    result *= objectColor;
    return result;
}
vec3 calDirLight(DirLight light){

    vec3 ambient = light.lightColor * materialAmbient;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.lightDir);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.lightColor * (diff * materialDiffuse);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininess);
    vec3 specular = light.lightColor * (spec * materialSpecluar);

    ambient  *= light.lightAmbient;
    specular *= light.lightSpecular;
    diffuse  *= light.lightDiffuse;
    vec3 result = (ambient + diffuse + specular);
    result *= objectColor;
    return result;
}
vec3 calSpotLight(SpotLight light){
    float theta = dot(normalize(light.lightDir), normalize(light.lightPos - FragPos));
    float epsilon   = light.lightInnerCutOff - light.lightOuterCutOff;
    float intensity = clamp((theta - light.lightOuterCutOff) / epsilon, 0.0, 1.0);

    vec3 ambient = light.lightColor * materialAmbient;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.lightColor * (diff * materialDiffuse);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininess);
    vec3 specular = light.lightColor * (spec * materialSpecluar);

    ambient  *= light.lightAmbient;
    specular *= light.lightSpecular;
    diffuse  *= light.lightDiffuse;
    if(isSpotLightAttenuation){
                float distance    = length(light.lightPos - FragPos);
                float attenuation = 1.0 / (light.lightConstant + light.lightLinear * distance + light.lightQuadratic * (distance * distance));
                ambient  *= attenuation;
            specular *= attenuation;
                diffuse *= attenuation;
        }
    diffuse  *= intensity;
    specular *= intensity;
    vec3 result = (ambient + diffuse + specular);
    result *= objectColor;
    return result;
}
