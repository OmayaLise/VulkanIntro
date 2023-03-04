#version 450

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragNormal;
//layout(location = 3) in vec3 viewPos;
//
layout(location = 0) out vec4 outColor;
layout(binding = 1) uniform sampler2D texSampler;

struct Light
{
    vec3 Position;
    vec3 Color;
};

Light lights[16];

void main()
{
    lights[0].Position = vec3(0.f, 0.f, 0.f);
    lights[0].Color = vec3(0.5f, 0.f, 0.f);

    lights[1].Position = vec3(0.f, -2.f, 0.f);
    lights[1].Color = vec3(0.f, 0.5f, 0.f);

    vec3 color = texture(texSampler, fragTexCoord).rgb;
    // lighting
    vec3 lighting = vec3(0.0);
    // ambient
    vec3 ambient = 0.1f * color;

    for (int i = 0; i < 2; i++)
    {
        // diffuse
        vec3 lightDir = normalize(lights[i].Position - fragPos);
        vec3 normal = normalize(fragNormal);
        float diff = max(dot(lightDir, normal), 0.0);
        vec3 diffuse = lights[i].Color * diff * color;      
        
    // specular
//        vec3 viewDir = normalize(viewPos - fragPos);
//        vec3 reflectDir = reflect(-lightDir, normal);
//        vec3 halfwayDir = normalize(lightDir + viewDir);
//        float spec = pow(max(dot(normal, halfwayDir), 0.0), 32);
//        vec3 specular = vec3(1.0) * spec;
    
//        vec3 result = diffuse + specular;
        vec3 result = diffuse ;
        float distance = length(fragPos - lights[i].Position);
        result *= 1.0 / (distance * distance);
        lighting += result;
    }
    outColor = vec4(ambient + lighting, 1.0);

}
