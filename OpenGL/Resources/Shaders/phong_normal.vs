#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;
layout (location = 3) in vec3 tanget;


out vec3 fragment_position;
out vec3 fragment_normal;
out vec2 fragment_uv;
out mat3 fragment_tbn;
out vec3 fragment_position_to_light;
out vec3 fragment_position_to_view;

uniform mat4		model_view_matrix;
uniform mat4		model_view_projection_matrix;
uniform mat3		normal_matrix;
uniform vec4		light_position;

//uniform vec2 uv_offset = vec2(0.0, 0.0);
//uniform vec2 uv_scale = vec2(1.0, 1.0);

void main()
{
	fragment_position = vec3(model_view_matrix * vec4(position, 1.0));
	
	vec3 transform_normal = normalize(normal_matrix * normal);
	vec3 transform_tanget = normalize(normal_matrix * tanget);
	vec3 transfomr_bitanget = cross(transform_normal, transform_tanget);

	//fragment_tbn = mat3(transform_tanget, transfomr_bitanget, transform_normal);
	fragment_tbn = inverse(mat3(transform_tanget, transfomr_bitanget, transform_normal));
	fragment_position_to_light = fragment_tbn * normalize(light_position.xyz - fragment_position);
	fragment_position_to_view = fragment_tbn * normalize(-fragment_position);

	fragment_uv = uv;

	gl_Position = model_view_projection_matrix * vec4(position.x, position.y, position.z, 1.0);
}