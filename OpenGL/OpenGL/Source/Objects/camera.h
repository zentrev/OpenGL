#pragma once

#include "core/object.h"
#include "core/engine.h"

class Camera : public Object
{
	public:
	enum eType
	{
		EDITOR,
		LOOK_AT
	};

public:

	Camera(Scene* scene, const std::string& name = "") : Object(scene, name) {}

	void Initialize();
	void Update();

	void SetView(const glm::vec3& position, const glm::vec3& target, const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f));
	void SetProjection(float fov, float nearClip, float farClip);

	void UpdateLookAt(glm::vec3& translate, glm::vec3& rotate);
	void UpdateEditor(glm::vec3& translate, glm::vec3& rotate);


	//void Edit() override;

public:
	eType type = eType::EDITOR;
	glm::mat4 projection;
	float m_rate = 5.0f;
};
