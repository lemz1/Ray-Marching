#version 460 core
out vec4 fragColor;

in vec2 v_TextureCoord;

void main()
{
	fragColor = vec4(v_TextureCoord, 0.0, 1.0);
}