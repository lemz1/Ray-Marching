#pragma once

#include <glm/glm.hpp>

struct Material
{
public:
	Material(glm::vec3 diffuseColor = glm::vec3(1))
		: diffuseColor(diffuseColor)
	{}

	glm::vec3 diffuseColor;
};