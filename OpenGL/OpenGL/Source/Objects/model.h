#pragma once

#include "core/object.h"
#include "core/engine.h"

class Model : public Object
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