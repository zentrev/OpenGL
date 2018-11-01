#pragma once

#include "core/object.h"
#include "core/engine.h"
#include "light.h"

class PointLight : public Light
{
public:
	PointLight(Scene* scene, const std::string& name = "") : Light(scene, name) {}

	glm::vec4 GetPositionFromView(const glm::mat4& mxView);
};