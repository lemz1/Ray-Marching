#pragma once

#include <glad/glad.h>

class StorageBuffer
{
public:
	StorageBuffer() = default;
	StorageBuffer(const void* data, GLsizeiptr size, GLuint index);
	~StorageBuffer();

	void SetData(const void* data, GLsizeiptr size);

	const void BindBufferBase() const;
	const void UnbindBufferBase() const;

	const GLuint GetID() const { return m_ID; }
private:
	GLuint m_ID;
	GLuint m_Index;
};