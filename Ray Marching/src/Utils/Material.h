#pragma once

#include <glm/glm.hpp>

struct Material
{
public:
	Material(glm::vec3 ambientColor = glm::vec3(0.2f), glm::vec3 diffuseColor = glm::vec3(0.8f))
		: ambientColor(ambientColor), diffuseColor(diffuseColor)
	{}

	glm::vec3 ambientColor, diffuseColor;
};