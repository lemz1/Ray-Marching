#include "RayHelpers.h"

// Unused Code leaving it here to remember this failure for calculating rays
RayHelpers::CameraInfo RayHelpers::CalculateCameraInfo(std::shared_ptr<Camera> camera)
{
	Transform cameraTransform = camera->GetTransform();

	constexpr float pi = 3.1415926f;
	float theta = pi / 180.f * camera->GetVerticalFOV();
	float height = 2.f * tan(theta / 2.f);
	float width = height * ((float)camera->GetWidth() / (float)camera->GetHeight());
	
	constexpr glm::vec3 y = glm::vec3(0, 1, 0);
	glm::vec3 w = glm::normalize(cameraTransform.rotation);
	glm::vec3 u = glm::normalize(glm::cross(w, y));
	glm::vec3 v = glm::cross(u, w);

	glm::vec3 horizontalComp = width * u;
	glm::vec3 verticalComp = height * v;
	glm::vec3 bottomLeft = cameraTransform.position - (horizontalComp / 2.f) - (verticalComp / 2.f) + w;

    return CameraInfo(horizontalComp, verticalComp, bottomLeft);
}
