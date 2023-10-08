#pragma once

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "Mesh.h"
#include "Shader.h"

class Quad
{
public:
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