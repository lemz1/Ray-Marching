#version 460 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TextureCoord;

out vec2 v_TextureCoord;

uniform mat4 u_TransformMatrix;
uniform mat4 u_ViewProjectionMatrix;

void main()
{
    gl_Position = u_ViewProjectionMatrix * u_TransformMatrix * vec4(a_Position, 1.0);
    v_TextureCoord = a_TextureCoord;
}
