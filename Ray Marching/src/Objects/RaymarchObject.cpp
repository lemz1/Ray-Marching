#include "RaymarchObject.h"

RaymarchObject* RaymarchObject::Create(
	const Transform& transform,
	const Material& material,
	const RaymarchObjectType& type,
	float blendStrength,
	const CombineType& combineType,
	const std::vector<RaymarchObject*>& children
)
{
	RaymarchObject* raymarchObject = new RaymarchObject();
	raymarchObject->object = ComputeRaymarchObject(transform, material, type, combineType, blendStrength, static_cast<uint32_t>(children.size()));
	raymarchObject->children = children;
	raymarchObject->combineType = combineType;
	return raymarchObject;
}

RaymarchObject* RaymarchObject::Create(
	const ComputeRaymarchObject& object,
	const CombineType& combineType,
	const std::vector<RaymarchObject*>& children
)
{
	RaymarchObject* raymarchObject = new RaymarchObject();
	raymarchObject->object = object;
	raymarchObject->children = children;
	raymarchObject->combineType = combineType;
	return raymarchObject;
}

void RaymarchObject::AddChild(RaymarchObject* object)
{
	children.push_back(object);
	this->object.numChildren++;
}

void RaymarchObject::SetChildren(const std::vector<RaymarchObject*>& objects)
{
	children = objects;
	this->object.numChildren = objects.size();
}
