#pragma once

#include <glad/glad.h>

#include <cstdint>

enum RenderBufferFormat
{
	DEPTH24STENCIL8 = GL_DEPTH24_STENCIL8,
};

struct RenderBufferSpecification
{
	uint32_t width, height;
	RenderBufferFormat format = RenderBufferFormat::DEPTH24STENCIL8;
};
