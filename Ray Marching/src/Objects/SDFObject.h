#pragma once

#include "../Utils/Transform.h"

enum SDFObjectType
{
	Sphere = 0,
	Box = 1,
	Torus = 2
};

struct SDFObject
{
public:
	SDFObject(const Transform& transform = Transform(), SDFObjectType type = SDFObjectType::Sphere) 
		: transform(transform), type(type)
	{}

	Transform transform;
	SDFObjectType type;
};


/*
struct SDFObject
{
public:
	SDFObject(const glm::vec3& position = glm::vec3(0), const glm::vec3& rotation = glm::vec3(0), 
			  const glm::vec3& scale = glm::vec3(1), SDFObjectType type = SDFObjectType::Sphere)
		: position(position), rotation(rotation), scale(scale), type(type)
	{}

	glm::vec3 position, rotation, scale;
	SDFObjectType type;
};
*/
