#pragma once

#include <vector>

#include <glad/glad.h>

#include "../Utils/Specifications/TextureSpecification.h"
#include "../Utils/Specifications/RenderBufferSpecification.h"

class FrameBuffer
{
public:
	FrameBuffer();
	~FrameBuffer();

	void AddTexture(const TextureSpecification& spec);
	void AddRenderBuffer(const RenderBufferSpecification& spec);
	
	const void Bind() const;
	const void Unbind() const;

	const TextureSpecification& GetTextureSpecification(uint32_t index) { return m_TextureSpecifications[index]; }
	void SetTextureSpecification(const TextureSpecification& spec, uint32_t index);

	const RenderBufferSpecification& GetRenderBufferSpecification(uint32_t index) { return m_RenderBufferSpecifications[index]; }
	void SetRenderBuffereSpecification(const RenderBufferSpecification& spec, uint32_t index);

	const GLuint GetID() const { return m_ID; }

	const GLuint GetTextureID(uint32_t index) const { return m_TextureIDs[index]; }
	const GLuint GetRenderBufferID(uint32_t index) const { return m_RenderBufferIDs[index]; }
private:
	GLuint m_ID;

	std::vector<GLuint> m_TextureIDs;
	std::vector<TextureSpecification> m_TextureSpecifications;

	std::vector<GLuint> m_RenderBufferIDs;
	std::vector<RenderBufferSpecification> m_RenderBufferSpecifications;
};