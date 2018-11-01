#include "point_light.h"

glm::vec4 PointLight::GetPositionFromView(const glm::mat4& mxView)
{
	return mxView * transform.matrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}
