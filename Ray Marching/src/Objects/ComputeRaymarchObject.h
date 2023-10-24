#pragma once

#include "RaymarchObjectType.h"
#include "CombineType.h"
#include "../Utils/Transform.h"
#include "../Utils/Material.h"

struct ComputeRaymarchObject
{
public:
	ComputeRaymarchObject(
		const Transform& transform = Transform(),
		const Material& material = Material(),
		const RaymarchObjectType& type = RaymarchObjectType::Sphere,
		const CombineType& combineType = CombineType::Blend,
		float blendStrength = 0.1f,
		uint32_t numChildren = 0
	)
		: transform(transform), material(material), type(type), combineType(combineType), blendStrength(blendStrength), numChildren(numChildren)
	{}
public:
	Transform transform;
	Material material;
	RaymarchObjectType type;
	CombineType combineType;
	float blendStrength;
	uint32_t numChildren;
};
