#pragma once

#include "core/object.h"
#include "core/engine.h"
#include "light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight(Scene* scene, const std::string& name = "") : Light(scene, name) {}

	glm::vec4 GetDirectionFromView(const glm::mat4& mxView);
};