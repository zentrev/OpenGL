#pragma once
#include "core/engine.h"

struct Transform
{
	glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::quat rotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
	glm::vec3 scale = glm::vec3(1.0f);

	glm::mat4 matrix = glm::mat4(1.0f);

	void Update()
	{
		glm::mat4 mxt  = glm::translate(glm::mat4(1.0f), translation);
		glm::mat4 mxr = glm::mat4_cast(rotation);
		glm::mat4 mxs  = glm::scale(glm::mat4(1.0f), scale);

		matrix = mxt * mxr * mxs;
	}
};