#version 110

attribute vec2 inPosition;  // Vertex position
attribute vec2 inTexCoord;  // Texture coordinates

varying vec2 fragTexCoord;  // Pass texture coordinates to fragment shader

void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    gl_FrontColor = gl_Color;
    fragTexCoord = gl_TexCoord[0].xy;
}