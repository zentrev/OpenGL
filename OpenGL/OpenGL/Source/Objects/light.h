#pragma once

#include "core/object.h"
#include "core/engine.h"

class Light : public Object
{
public:
	Light(Scene* scene, const std::string& name = "") : Object(scene, name) {}
	
	virtual void Update();
	
public:
	glm::vec3 diffuse;
	glm::vec3 specular;
};