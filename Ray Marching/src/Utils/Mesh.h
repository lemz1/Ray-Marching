#pragma once

#include <vector>
#include <glm/glm.hpp>

struct Mesh
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texCoords;
	std::vector<uint32_t> indices;
};
