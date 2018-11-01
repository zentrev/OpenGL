#include "directional_light.h"

glm::vec4 DirectionalLight::GetDirectionFromView(const glm::mat4& mxView)
{
	glm::vec3 direction = glm::mat3(mxView * transform.matrix) * glm::vec3(0.0f, 0.0f, -1.0f);
	return glm::vec4(direction, 0.0f);
}
