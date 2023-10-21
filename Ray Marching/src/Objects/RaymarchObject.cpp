#include "RaymarchObject.h"

RaymarchObject* RaymarchObject::Create(const ComputeRaymarchObject& object, const std::vector<RaymarchObject> children, const CombineType& combineType)
{
	RaymarchObject* raymarchObject = new RaymarchObject();
	raymarchObject->object = object;
	raymarchObject->children = children;
	raymarchObject->combineType = combineType;
	return raymarchObject;
}
