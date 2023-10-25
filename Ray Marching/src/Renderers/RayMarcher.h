#pragma once

#include <memory>
#include <vector>

#include "../Utils/Shader.h"
#include "../Utils/Camera.h"
#include "../Objects/RaymarchObject.h"
#include "../Objects/PointLight.h"
#include "../Objects/DirectionalLight.h"
#include "../BufferObjects/StorageBuffer.h"

class RayMarcher
{
public:
	static RayMarcher* Create(
		const std::shared_ptr<Shader>& computeShader,
		const std::shared_ptr<Camera>& camera,
		const std::vector<RaymarchObject*>& objects = std::vector<RaymarchObject*>(),
		const std::vector<PointLight>& pointLights = std::vector<PointLight>(),
		const std::vector<DirectionalLight>& directionalLights = std::vector<DirectionalLight>()
	);
	~RayMarcher();

	void AddObject(RaymarchObject* object);
	void AddPointLight(const PointLight& pointLight);
	void AddDirectionalLight(const DirectionalLight& directionalLight);

	const float GetBlendStrength() const { return m_BlendStrength; }
	void SetBlendStrength(float blendStrength) { m_BlendStrength = glm::clamp(blendStrength, 0.f, 1.f); }

	const std::vector<RaymarchObject*>& GetObjects() const { return m_Objects; }
	std::vector<RaymarchObject*>& GetObjects() { return m_Objects; }

	const std::vector<PointLight>& GetPointLights() const { return m_PointLights; }
	std::vector<PointLight>& GetPointLights() { return m_PointLights; }

	const std::vector<DirectionalLight>& GetDirectionalLights() const { return m_DirectionalLights; }
	std::vector<DirectionalLight>& GetDirectionalLights() { return m_DirectionalLights; }

	const std::vector<ComputeRaymarchObject>& GetComputeObjects() const { return m_ComputeObjects; }
	std::vector<ComputeRaymarchObject>& GetComputeObjects() { return m_ComputeObjects; }
	
	void Render();
private:
	void CreateBuffers();
	void DeleteBuffers();

	void AddChildrenRecursively(const RaymarchObject* object);
private:
	std::shared_ptr<Shader> m_ComputeShader;
	std::shared_ptr<Camera> m_Camera;

	float m_BlendStrength = 0;

	std::vector<RaymarchObject*> m_Objects;
	std::vector<PointLight> m_PointLights;
	std::vector<DirectionalLight> m_DirectionalLights;

	std::vector<ComputeRaymarchObject> m_ComputeObjects;

	StorageBuffer* m_ObjectsBuffer = nullptr;
	StorageBuffer* m_PointLightsBuffer = nullptr;
	StorageBuffer* m_DirectionalLightsBuffer = nullptr;
};