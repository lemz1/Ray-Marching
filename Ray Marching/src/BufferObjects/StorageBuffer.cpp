#include "StorageBuffer.h"

StorageBuffer::StorageBuffer(const void* data, GLsizeiptr size, GLuint index)
	: m_Index(index)
{
	glCreateBuffers(1, &m_ID);
	SetData(data, size);
}

StorageBuffer::~StorageBuffer()
{
	glDeleteBuffers(1, &m_ID);
}

void StorageBuffer::SetData(const void* data, GLsizeiptr size)
{
	glNamedBufferData(m_ID, size, data, GL_DYNAMIC_DRAW);
}

const void StorageBuffer::BindBufferBase() const
{
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, m_Index, m_ID);
}

const void StorageBuffer::UnbindBufferBase() const
{
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, m_Index, 0);
}
