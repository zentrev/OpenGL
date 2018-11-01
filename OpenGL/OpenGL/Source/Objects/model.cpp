#include "model.h"
#include "core/scene.h"

Model::Model(Scene* scene, const std::string& name) : Object(scene, name)
{
	//
}

void Model::Update()
{
	transform.Update();
}

void Model::Draw()
{
	m_shader.Use();
	m_material.SetTextures();
	m_vertexArrays.Draw();
}
