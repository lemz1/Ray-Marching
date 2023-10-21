#pragma once

#include <vector>

#include "ComputeRaymarchObject.h"
#include "CombineType.h"

// im doing it likes this to have the ability to do recursive effects
// for example: 
//	object: Mask
//		object: Blend
//			object: None
//			object: None
//		object: Substract
//			object: None
// 
// also if a RayMarchObject doesnt have any children 
// the CombineType is going to be ignored

struct RaymarchObject
{
public:
	static RaymarchObject* Create(const ComputeRaymarchObject& object, const std::vector<RaymarchObject> children, const CombineType& combineType = CombineType::None);
public:
	ComputeRaymarchObject object;
	std::vector<RaymarchObject> children;
	CombineType combineType = CombineType::None;
};