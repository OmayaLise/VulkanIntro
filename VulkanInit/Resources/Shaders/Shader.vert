#version 450

layout(binding = 0) uniform UniformBufferObject 
{
    mat4 model;
    mat4 view;
    mat4 proj;
    vec3 camPos;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inNormal;

layout(location = 0) out vec3 fragPos;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 fragNormal;
//layout(location = 3) out vec3 viewPos;
//

bool inverse_normals = false;

void main()
{
    fragPos = vec3(ubo.model * vec4(inPosition, 1.0));   
    fragTexCoord = inTexCoord;
    
    vec3 n = inverse_normals ? -inNormal : inNormal;
    
    mat3 normalMatrix = transpose(inverse(mat3(ubo.model)));
    fragNormal = normalize(normalMatrix * n);
    
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);

}