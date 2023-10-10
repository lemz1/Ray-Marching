#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct MouseMoveEvent
{
public:
	MouseMoveEvent(double positionX, double postionY) 
		: m_PositionX(positionX), m_PositionY(postionY)
	{}

	const double GetPositionX() const { return m_PositionX; }
	const double GetPositionY() const { return m_PositionY; }
private:
	double m_PositionX, m_PositionY;
};
