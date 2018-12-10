#version 430 core

in vec3 fragment_position;
in vec3 fragment_normal;
in vec2 fragment_uv;
in vec4 fragment_position_light;

struct material_s
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct light_s
{
	vec4 position;
	vec3 diffuse;
	vec3 specular;
};

uniform light_s		light;
uniform material_s	material;
uniform mat4		model_view_matrix;
uniform mat4		model_view_projectil_matrix;
uniform mat3		normal_matrix;

layout (binding = 0) uniform sampler2D textureSample;
layout (binding = 1) uniform sampler2DShadow shadowSample;
out vec4 color;

void main()
{
    
    vec3 position_to_light;
	vec3 ambient = material.ambient;
	vec3 specular;


    if (light.position.w == 0.0)
    {
        position_to_light = normalize(vec3(light.position));
    }
    else
    {
        position_to_light = normalize(vec3(light.position) - fragment_position);
    }

	float diffuse_intensity = max(dot(position_to_light, fragment_normal), 0.0);
	vec3 diffuse = material.diffuse * light.diffuse * diffuse_intensity;

	if (diffuse_intensity > 0.0)
	{
		vec3 position_to_view = normalize(-fragment_position.xyz);
		vec3 reflect_light = reflect(-position_to_light, fragment_normal);
		float specular_intensity = max(dot(reflect_light, position_to_view), 0.0);
		specular_intensity = pow(specular_intensity, material.shininess);
		specular = light.specular * material.specular * specular_intensity;
	}

	float shadow = 1.0f;
	if(fragment_position_light.z >= 0)
	{
		shadow = textureProj(shadowSample, fragment_position_light);
	}
	color = texture(textureSample, fragment_uv) * vec4(ambient + ((diffuse + specular) * shadow), 1.0);
}
