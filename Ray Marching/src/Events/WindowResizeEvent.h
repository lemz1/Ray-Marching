#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdint>

struct WindowResizeEvent
{
public:
	WindowResizeEvent(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height)
	{}

	const uint32_t GetWidth() const { return m_Width; }
	const uint32_t GetHeight() const { return m_Height; }
private:
	uint32_t m_Width, m_Height;
};
