#include "model.h"
#include "core/scene.h"
#include "Objects/camera.h"

Model::Model(Scene* scene, const std::string& name) : Renderable(scene, name)
{
	//
}

void Model::Update()
{
	transform.Update();

	Camera * camera = scene->GetObject<Camera>();

	m_shader.Use();

	// update normals
	glm::mat3 mxNormal = glm::mat3(camera->transform.matrix * transform.matrix);
	mxNormal = glm::inverse(mxNormal);
	mxNormal = glm::transpose(mxNormal);
	m_shader.SetUniform("normal_matrix", mxNormal);

	// update model view
	glm::mat4 mxMV = camera->transform.matrix * transform.matrix;
	m_shader.SetUniform("model_view_matrix", mxMV);

	// update mvp
	glm::mat4 mxMVP = camera->projection * camera->transform.matrix * transform.matrix;
	m_shader.SetUniform("model_view_projection_matrix", mxMVP);

	
}

void Model::Draw()
{
	m_shader.Use();
	m_material.SetTextures();
	m_vertexArrays.Draw();
}
