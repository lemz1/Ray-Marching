#version 460 core
out vec4 fragColor;

in vec2 v_TextureCoord;

uniform sampler2D u_Texture;

void main()
{
	fragColor = texture(u_Texture, v_TextureCoord);
}
