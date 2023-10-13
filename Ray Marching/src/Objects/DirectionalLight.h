#pragma once

#include <glm/glm.hpp>

struct DirectionalLight
{
public:
	DirectionalLight(glm::vec3 direction = glm::vec3(0), glm::vec3 color = glm::vec3(1))
		: direction(direction), color(color)
	{}

	glm::vec3 direction = glm::vec3(0);
	glm::vec3 color = glm::vec3(1);
};