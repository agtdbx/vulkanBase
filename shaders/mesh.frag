#version 450

layout(binding = 1)  uniform sampler2D sampleTexture;

// Input from vertex
layout(location = 0) in vec2    fragTexCoord;

// Output
layout(location = 0) out vec4   outColor;

// Constants

// Functions

// Main
void main()
{
    outColor = texture(sampleTexture, fragTexCoord);
}
