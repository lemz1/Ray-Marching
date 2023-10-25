#pragma once

#include <glm/glm.hpp>

struct PointLight
{
public:
	PointLight(glm::vec3 position = glm::vec3(0), glm::vec3 color = glm::vec3(1), float intensity = 2) 
		: position(position), color(color), intensity(intensity)
	{}

	glm::vec3 position;
	glm::vec3 color;
	float intensity;
};