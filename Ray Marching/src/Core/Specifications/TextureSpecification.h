#pragma once

#include <glad/glad.h>

#include <cstdint>

enum TextureFormat
{
	RGBA8 = GL_RGBA8,
	RGBA32F = GL_RGBA32F,
};

struct TextureSpecification
{
	uint32_t width, height = 0;
	TextureFormat format = TextureFormat::RGBA8;
};
