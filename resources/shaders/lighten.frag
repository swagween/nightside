#version 330 core

in vec2 fragTexCoord;  // The texture coordinates passed from the vertex shader
uniform sampler2D textureSampler;  // The texture uniform to sample from

out vec4 fragColor;  // The output color of the fragment

void main()
{
    fragColor = texture(textureSampler, fragTexCoord);  // Sample the texture and assign to fragColor
}