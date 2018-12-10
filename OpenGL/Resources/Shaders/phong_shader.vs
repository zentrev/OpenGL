#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out vec3 fragment_position;
out vec3 fragment_normal;
out vec2 fragment_uv;
out vec4 fragment_position_light;

uniform mat4		model_view_matrix;
uniform mat4		model_view_projection_matrix;
uniform mat4		light_view_projection_matrix;
uniform mat3		normal_matrix;

uniform vec2 uv_offset = vec2(0.0, 0.0);
uniform vec2 uv_scale = vec2(1.0, 1.0);

void main()
{
	fragment_position = vec3(model_view_matrix * vec4(position, 1.0));
	fragment_normal = normalize(normal_matrix * normal);
	fragment_uv = uv;
	fragment_position_light = light_view_projection_matrix * vec4(position, 1.0f);

	gl_Position = model_view_projection_matrix * vec4(position.x, position.y, position.z, 1.0);
}