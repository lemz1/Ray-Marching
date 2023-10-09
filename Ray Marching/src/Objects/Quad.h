#pragma once

#include "../BufferObjects/VertexArray.h"
#include "../BufferObjects/VertexBuffer.h"
#include "../BufferObjects/ElementBuffer.h"
#include "../Utils/Mesh.h"
#include "../Utils/Shader.h"

class Quad
{
public:
	Quad() = default;
	Quad(std::shared_ptr<Shader> shader);
	~Quad();

	void Draw();
private:
	Mesh m_Mesh;
	std::shared_ptr<Shader> m_Shader;

	VertexArray* m_VertexArray;
	VertexBuffer* m_VertexBuffer;
	VertexBuffer* m_TexCoordBuffer;
	ElementBuffer* m_ElementBuffer;
};