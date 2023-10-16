#pragma once

#include <memory>

#include "../Utils/Transform.h"
#include "../Utils/Mesh.h"
#include "../Utils/Shader.h"
#include "../Utils/Camera.h"


#include "../BufferObjects/VertexArray.h"
#include "../BufferObjects/VertexBuffer.h"
#include "../BufferObjects/ElementBuffer.h"


class Quad
{
public:
	Quad(const Transform& transform, std::shared_ptr<Camera> camera);
	~Quad();

	void Draw();

	const Transform& GetTransform() { return m_Transform; }
private:
	void CreateBuffers();
private:
	Transform m_Transform;
	Mesh m_Mesh;

	std::shared_ptr<Shader> m_Shader;
	std::shared_ptr<Camera> m_Camera;

	VertexArray* m_VAO;
	VertexBuffer* m_VBO;
	VertexBuffer* m_UVBO;
	ElementBuffer* m_EBO;
};