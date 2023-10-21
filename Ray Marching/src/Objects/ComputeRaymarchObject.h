#pragma once

#include "RaymarchObjectType.h"
#include "../Utils/Transform.h"
#include "../Utils/Material.h"

struct ComputeRaymarchObject
{
public:
	ComputeRaymarchObject(
		const Transform& transform = Transform(), 
		const Material& material = Material(), 
		RaymarchObjectType type = RaymarchObjectType::Sphere, 
		float blendStrength = 0.1f
	)
		: transform(transform), material(material), type(type), blendStrength(blendStrength)
	{}
public:

	Transform transform;
	Material material;
	RaymarchObjectType type;
	float blendStrength;
};
