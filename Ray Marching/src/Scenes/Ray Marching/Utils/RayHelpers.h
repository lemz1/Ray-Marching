#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "../../../Utils/Camera.h"

namespace RayHelpers
{
	// pretty descriptive isnt it
	struct CameraInfo
	{
	public:
		CameraInfo(glm::vec3 horizontalComp, glm::vec3 verticalComp, glm::vec3 bottomLeft) 
			: horizontalComp(horizontalComp), verticalComp(verticalComp), bottomLeft(bottomLeft)
		{}

		glm::vec3 horizontalComp, verticalComp, bottomLeft;
	};

	CameraInfo CalculateCameraInfo(std::shared_ptr<Camera> camera);
}