#version 330 core


// Input vertex attributes (position and texture coordinates)
in vec2 inPosition;  // Vertex position (from the vertex buffer)
in vec2 inTexCoord;  // Texture coordinates (from the vertex buffer)

// Output to the fragment shader
out vec2 fragTexCoord;  // Pass texture coordinates to fragment shader

void main()
{
    gl_Position = vec4(inPosition, 0.0, 1.0);  // Pass the position directly to OpenGL
    fragTexCoord = inTexCoord;  // Pass the texture coordinates to the fragment shader
}