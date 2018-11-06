#pragma once

#include "core/object.h"
#include "core/engine.h"
#include "renderable.h"

class Model : public Renderable
{
public:
	Model(Scene* scene, const std::string& name = "");

	virtual void Update();
	void Draw();

public:
	VertexArrays m_vertexArrays;
	Shader m_shader;
	Material m_material;
};