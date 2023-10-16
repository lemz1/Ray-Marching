#include "Quad.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Mesh CreateQuadMesh()
{
	return Mesh
	{
		std::vector<glm::vec3>
		{
			glm::vec3(-1, 1, 0),
			glm::vec3(1, 1, 0),
			glm::vec3(-1, -1, 0),
			glm::vec3(1, -1, 0),
		},
		std::vector<glm::vec2>
		{
			glm::vec2(0, 1),
			glm::vec2(1, 1),
			glm::vec2(0, 0),
			glm::vec2(1, 0),
		},
		std::vector<uint32_t>
		{
			0, 1, 2,
			1, 3, 2
		}
	};
}

Quad::Quad(const Transform& transform, std::shared_ptr<Camera> camera)
	: m_Transform(transform), m_Mesh(CreateQuadMesh()), m_Camera(camera)
{
	CreateBuffers();

	m_Shader = Shader::CreateVertexFragmentShader(
		"assets/shaders/default.vert",
		"assets/shaders/default.frag"
	);
}

Quad::~Quad()
{
	delete m_VAO;
	delete m_VBO;
	delete m_UVBO;
	delete m_EBO;
}

void Quad::Draw()
{
	m_Shader->StartProgram();
	m_VAO->Bind();

	GLuint transformMatrixLocation = glGetUniformLocation(m_Shader->GetID(), "u_TransformMatrix");
	// Convert transform struct to transformation matrix
	glm::mat4 transformMatrix = glm::mat4(1.0f); // Start with identity matrix
	transformMatrix = glm::translate(transformMatrix, m_Transform.position); // Apply translation
	transformMatrix = glm::rotate(transformMatrix, glm::radians(m_Transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // Apply rotation in x-axis
	transformMatrix = glm::rotate(transformMatrix, glm::radians(m_Transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Apply rotation in y-axis
	transformMatrix = glm::rotate(transformMatrix, glm::radians(m_Transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Apply rotation in z-axis
	transformMatrix = glm::scale(transformMatrix, m_Transform.scale); // Apply scale

	// Pass transformation matrix to shader
	glUniformMatrix4fv(transformMatrixLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));

	GLuint viewProjectionMatrixLocation = glGetUniformLocation(m_Shader->GetID(), "u_ViewProjectionMatrix");
	glUniformMatrix4fv(viewProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_Camera->GetViewProjectionMatrix()));
	
	glDrawElements(GL_TRIANGLES, m_Mesh.indices.size(), GL_UNSIGNED_INT, 0);

	m_VAO->Unbind();
	m_Shader->StopProgram();
}

void Quad::CreateBuffers()
{
	m_VBO = new VertexBuffer(m_Mesh.vertices.data(), m_Mesh.vertices.size() * sizeof(glm::vec3));
	m_UVBO = new VertexBuffer(m_Mesh.texCoords.data(), m_Mesh.texCoords.size() * sizeof(glm::vec2));
	m_EBO = new ElementBuffer(m_Mesh.indices.data(), m_Mesh.indices.size() * sizeof(uint32_t));

	m_VAO = new VertexArray();
	m_VAO->LinkVertexBuffer(m_VBO->GetID(), 0, 3);
	m_VAO->LinkVertexBuffer(m_UVBO->GetID(), 1, 2);
	m_VAO->LinkElementBuffer(m_EBO->GetID());
}