#include "FrameBuffer.h"

#include <iostream>

void FrameBuffer::CreateTexture(GLuint* textureID, const TextureSpecification& spec, uint32_t index)
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

	glGenTextures(1, textureID);
	glBindTexture(GL_TEXTURE_2D, *textureID);

	switch (spec.format)
	{
		case TextureFormat::RGBA8:
		{
			glTexImage2D(GL_TEXTURE_2D, index, spec.format, spec.width, spec.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		}
		break;
		case TextureFormat::RGBA32F:
		{
			glTexImage2D(GL_TEXTURE_2D, index, spec.format, spec.width, spec.height, 0, GL_RGBA, GL_FLOAT, nullptr);
		}
		break;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// idk if GL_COLOR_ATTACHMENT0 + index is correct, 
	// i think it is because GL_COLOR_ATTACHMENT1 is GL_COLOR_ATTACHMENT_0 + 1 
	// so i believe this works (im not going to test it, since i dont need it)
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, *textureID, index);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::CreateRenderBuffer(GLuint* renderBufferID, const RenderBufferSpecification& spec, uint32_t index)
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

	glGenRenderbuffers(1, renderBufferID);
	glBindRenderbuffer(GL_RENDERBUFFER, *renderBufferID);

	switch (spec.format)
	{
		case RenderBufferFormat::DEPTH24STENCIL8:
		{
			glRenderbufferStorage(GL_RENDERBUFFER, spec.format, spec.width, spec.height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, *renderBufferID);
		}
		break;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

FrameBuffer::FrameBuffer()
{
	glCreateFramebuffers(1, &m_ID);
}

FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_ID);

	for (GLuint textureID : m_TextureIDs)
	{
		glDeleteTextures(1, &textureID);
	}

	for (GLuint renderBufferID : m_RenderBufferIDs)
	{
		glDeleteRenderbuffers(1, &renderBufferID);
	}
}

void FrameBuffer::AddTexture(const TextureSpecification& spec)
{
	GLuint textureID;
	
	CreateTexture(&textureID, spec, m_TextureIDs.size());

	m_TextureIDs.push_back(textureID);
	m_TextureSpecifications.push_back(spec);

}

void FrameBuffer::AddRenderBuffer(const RenderBufferSpecification& spec)
{
	GLuint renderBufferID;

	CreateRenderBuffer(&renderBufferID, spec, m_RenderBufferIDs.size());

	m_RenderBufferIDs.push_back(renderBufferID);
	m_RenderBufferSpecifications.push_back(spec);
}

const void FrameBuffer::Bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
}

const void FrameBuffer::Unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


// both of these dont work functions dont work correctly
void FrameBuffer::SetTextureSpecification(const TextureSpecification& spec, uint32_t index)
{
	GLuint oldTextureID = GetTextureID(index);

	glDeleteTextures(1, &oldTextureID);

	GLuint textureID;

	CreateTexture(&textureID, spec, index);

	m_TextureIDs[index] = textureID;
	m_TextureSpecifications[index]= spec;
}

void FrameBuffer::SetRenderBufferSpecification(const RenderBufferSpecification & spec, uint32_t index)
{
	GLuint renderBufferID = GetRenderBufferID(index);

	glDeleteRenderbuffers(1, &renderBufferID);

	CreateRenderBuffer(&renderBufferID, spec, index);

	m_RenderBufferIDs[index] = renderBufferID;
	m_RenderBufferSpecifications[index] = spec;
}
