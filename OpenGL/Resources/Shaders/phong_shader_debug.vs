#version 430

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 uv;

out vec2 fragment_uv;

void main()
{
	fragment_uv = vec2(uv.x, 1.0 - uv.y);
	vec3 _position = (position * 0.4f) + vec3(-0.5f, 0.40f, 0.0f);
    	gl_Position = vec4(_position, 1.0);
}
