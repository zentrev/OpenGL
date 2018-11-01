#pragma once

#include "core/object.h"
#include "core/engine.h"

class Camera : public Object
{
public:
	Camera(Scene* scene, const std::string& name = "") : Object(scene, name) {}

	void Initialize();
	void Update();

	void SetView(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f));
	void SetProjection(float fov, float nearClip, float farClip);

public:
	glm::mat4 projection;
	float m_rate = 60.0f;
};
