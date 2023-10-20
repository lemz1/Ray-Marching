#include "RayMarcher.h"

#include <glm/gtc/type_ptr.hpp>

#include "../Core/Application.h"

RayMarcher* RayMarcher::Create(
	std::shared_ptr<Shader> computeShader,
	std::shared_ptr<Camera> camera,
	const std::vector<SDFObject>& objects, 
	const std::vector<PointLight>& pointLights, 
	const std::vector<DirectionalLight>& directionalLights
)
{
	RayMarcher* rayMarcher = new RayMarcher();
	rayMarcher->m_ComputeShader = computeShader;
	rayMarcher->m_Camera = camera;
	rayMarcher->m_Objects = objects;
	rayMarcher->m_PointLights = pointLights;
	rayMarcher->m_DirectionalLights = directionalLights;

	rayMarcher->CreateBuffers();

	return rayMarcher;
}

RayMarcher::~RayMarcher()
{
	DeleteBuffers();
}

void RayMarcher::AddObject(const SDFObject& object)
{
	m_Objects.push_back(object);
	m_ObjectsBuffer->SetData(m_Objects.data(), m_Objects.size() * sizeof(SDFObject));
}

void RayMarcher::AddPointLight(const PointLight& pointLight)
{
	m_PointLights.push_back(pointLight);
	m_PointLightsBuffer->SetData(m_PointLights.data(), m_PointLights.size() * sizeof(PointLight));
}

void RayMarcher::AddDirectionalLight(const DirectionalLight& directionalLight)
{
	m_DirectionalLights.push_back(directionalLight);
	m_DirectionalLightsBuffer->SetData(m_DirectionalLights.data(), m_DirectionalLights.size() * sizeof(DirectionalLight));
}

void RayMarcher::Render()
{
	GLuint textureID = Application::GetViewportFrameBuffer()->GetTextureID(0);
	TextureSpecification spec = Application::GetViewportFrameBuffer()->GetTextureSpecification(0);

	GLuint computeShaderID = m_ComputeShader->GetID();

	glUseProgram(computeShaderID);
	glUniform1ui(glGetUniformLocation(computeShaderID, "width"), spec.width);
	glUniform1ui(glGetUniformLocation(computeShaderID, "height"), spec.height);

	glUniform1ui(glGetUniformLocation(computeShaderID, "numSDFObjects"), static_cast<GLuint>(m_Objects.size()));
	glUniform1ui(glGetUniformLocation(computeShaderID, "numPointLights"), static_cast<GLuint>(m_PointLights.size()));
	glUniform1ui(glGetUniformLocation(computeShaderID, "numDirectionalLights"), static_cast<GLuint>(m_DirectionalLights.size()));

	Transform camT = m_Camera->GetTransform();
	glUniform3f(glGetUniformLocation(computeShaderID, "cameraOrigin"),
		camT.position.x,
		camT.position.y,
		camT.position.z);

	glUniformMatrix4fv(glGetUniformLocation(computeShaderID, "inverseProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(m_Camera->GetInverseProjectionMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(computeShaderID, "inverseViewMatrix"), 1, GL_FALSE, glm::value_ptr(m_Camera->GetInverseViewMatrix()));

	m_ObjectsBuffer->SetData(m_Objects.data(), m_Objects.size() * sizeof(SDFObject));
	m_PointLightsBuffer->SetData(m_PointLights.data(), m_PointLights.size() * sizeof(PointLight));
	m_DirectionalLightsBuffer->SetData(m_DirectionalLights.data(), m_DirectionalLights.size() * sizeof(DirectionalLight));

	m_ObjectsBuffer->BindBufferBase();
	m_PointLightsBuffer->BindBufferBase();
	m_DirectionalLightsBuffer->BindBufferBase();

	glBindImageTexture(0, textureID, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);
	glDispatchCompute(
		static_cast<GLuint>(ceil((float)spec.width / 16.f)),
		static_cast<GLuint>(ceil((float)spec.height / 16.f)),
		1);
	glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

	m_ObjectsBuffer->UnbindBufferBase();
	m_PointLightsBuffer->UnbindBufferBase();
	m_DirectionalLightsBuffer->UnbindBufferBase();

	glUseProgram(0);
}

void RayMarcher::CreateBuffers()
{
	m_ObjectsBuffer = new StorageBuffer(m_Objects.data(), m_Objects.size() * sizeof(SDFObject), 1);
	m_PointLightsBuffer = new StorageBuffer(m_PointLights.data(), m_PointLights.size() * sizeof(PointLight), 2);
	m_DirectionalLightsBuffer = new StorageBuffer(m_DirectionalLights.data(), m_DirectionalLights.size() * sizeof(DirectionalLight), 3);
}

void RayMarcher::DeleteBuffers()
{
	delete m_ObjectsBuffer;
	delete m_PointLightsBuffer;
	delete m_DirectionalLightsBuffer;
}
