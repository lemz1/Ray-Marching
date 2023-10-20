#pragma once

#include "../Utils/Transform.h"
#include "../Utils/Material.h"

enum SDFObjectType
{
	Sphere = 0,
	Box = 1,
	Torus = 2
};

struct SDFObject
{
public:
	SDFObject(const Transform& transform = Transform(), const Material& material = Material(), SDFObjectType type = SDFObjectType::Sphere, float blendStrength = 0.1f)
		: transform(transform), material(material), type(type), blendStrength(blendStrength)
	{}

	Transform transform;
	Material material;
	SDFObjectType type;
	float blendStrength;
};
