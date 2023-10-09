#include "FrameBuffer.h"

#include <iostream>

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
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

	GLuint textureID;
	
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	switch (spec.format)
	{
		case TextureFormat::RGBA8:
		{
			glTexImage2D(GL_TEXTURE_2D, m_TextureIDs.size(), spec.format, spec.width, spec.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		}
		break;
		case TextureFormat::RGBA32F:
		{
			glTexImage2D(GL_TEXTURE_2D, m_TextureIDs.size(), spec.format, spec.width, spec.height, 0, GL_RGBA, GL_FLOAT, nullptr);
		}
		break;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// idk if GL_COLOR_ATTACHMENT0 + m_TextureIDs.size() is correct, 
	// i think it is because GL_COLOR_ATTACHMENT1 is GL_COLOR_ATTACHMENT_0 + 1 
	// so i believe this works (im not going to test it, since i dont need it)
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_TextureIDs.size(), GL_TEXTURE_2D, textureID, m_TextureIDs.size());
	
	m_TextureIDs.push_back(textureID);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::AddRenderBuffer(const RenderBufferSpecification& spec)
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

	GLuint renderBufferID;

	glGenRenderbuffers(1, &renderBufferID);
	glBindRenderbuffer(GL_RENDERBUFFER, renderBufferID);

	switch (spec.format)
	{
		case RenderBufferFormat::DEPTH24STENCIL8:
		{
			glRenderbufferStorage(GL_RENDERBUFFER, spec.format, spec.width, spec.height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferID);
		}
		break;
	}
	
	m_RenderBufferIDs.push_back(renderBufferID);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

const void FrameBuffer::Bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
}

const void FrameBuffer::Unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::SetTextureSpecification(const TextureSpecification& spec, uint32_t index)
{
	GLuint textureID = GetTextureID(index);

	glBindTexture(GL_TEXTURE_2D, textureID);

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

}

void FrameBuffer::SetRenderBuffereSpecification(const RenderBufferSpecification & spec, uint32_t index)
{
	GLuint renderBufferID = GetRenderBufferID(index);

	glBindRenderbuffer(GL_RENDERBUFFER, renderBufferID);

	switch (spec.format)
	{
		case RenderBufferFormat::DEPTH24STENCIL8:
		{
			glRenderbufferStorage(GL_RENDERBUFFER, spec.format, spec.width, spec.height);
		}
		break;
	}
}
