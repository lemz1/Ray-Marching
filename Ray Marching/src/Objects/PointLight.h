#pragma once

#include <glm/glm.hpp>

enum LightFalloff
{
	None = 0,
	Linear = 1,
	Quadratic = 2
};

struct PointLight
{
public:
	PointLight(glm::vec3 position = glm::vec3(0), glm::vec3 color = glm::vec3(1), LightFalloff lightFalloffType = LightFalloff::Linear, float intensity = 2) 
		: position(position), color(color), lightFalloffType(lightFalloffType), intensity(intensity)
	{}

	glm::vec3 position;
	glm::vec3 color;
	LightFalloff lightFalloffType;
	float intensity;
};