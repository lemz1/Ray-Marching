#pragma once

#include <memory>
#include <vector>

#include "../Utils/Shader.h"
#include "../Utils/Camera.h"
#include "../Objects/SDFObject.h"
#include "../Objects/PointLight.h"
#include "../Objects/DirectionalLight.h"
#include "../BufferObjects/StorageBuffer.h"

class RayMarcher
{
public:
	static RayMarcher* Create(
		std::shared_ptr<Shader> computeShader, 
		std::shared_ptr<Camera> camera,
		const std::vector<SDFObject>& objects = std::vector<SDFObject>(),
		const std::vector<PointLight>& pointLights = std::vector<PointLight>(), 
		const std::vector<DirectionalLight>& directionalLights = std::vector<DirectionalLight>()
	);
	~RayMarcher();

	void AddObject(const SDFObject& object);
	void AddPointLight(const PointLight& pointLight);
	void AddDirectionalLight(const DirectionalLight& directionalLight);

	const std::vector<SDFObject>& GetObjects() const { return m_Objects; }
	std::vector<SDFObject>& GetObjects() { return m_Objects; }

	const std::vector<PointLight>& GetPointLights() const { return m_PointLights; }
	std::vector<PointLight>& GetPointLights() { return m_PointLights; }

	const std::vector<DirectionalLight>& GetDirectionalLights() const { return m_DirectionalLights; }
	std::vector<DirectionalLight>& GetDirectionalLights() { return m_DirectionalLights; }

	void Render();
private:
	void CreateBuffers();
	void DeleteBuffers();
private:
	std::shared_ptr<Shader> m_ComputeShader;
	std::shared_ptr<Camera> m_Camera;

	std::vector<SDFObject> m_Objects;
	std::vector<PointLight> m_PointLights;
	std::vector<DirectionalLight> m_DirectionalLights;

	StorageBuffer* m_ObjectsBuffer;
	StorageBuffer* m_PointLightsBuffer;
	StorageBuffer* m_DirectionalLightsBuffer;
};