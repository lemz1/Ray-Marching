#include "RayMarchingScene.h"

#include <glad/glad.h>

void RayMarchingScene::OnCreate()
{
	m_Shader = Shader::CreateVertexFragmentShader(
		"assets/shaders/default.vert",
		"assets/shaders/default.frag"
	);

	m_Quad = new Quad(m_Shader);
}

void RayMarchingScene::OnUpdate(double deltaTime)
{
	glClearColor(.1f, .1f, .1f, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	m_Quad->Draw();
}

void RayMarchingScene::OnDestroy()
{
	delete m_Quad;
}
