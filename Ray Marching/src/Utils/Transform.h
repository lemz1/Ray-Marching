#pragma once

#include <glm/glm.hpp>

struct Transform
{
public:
	Transform(glm::vec3 position = glm::vec3(0), glm::vec3 rotation = glm::vec3(0), glm::vec3 scale = glm::vec3(1))
		: position(position), rotation(rotation), scale(scale)
	{}
public:
	glm::vec3 position, rotation, scale;
};
