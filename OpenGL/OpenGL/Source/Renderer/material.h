#pragma once

#include "core/engine.h"

class Material
{
public:
	Material() {}

	void AddTexture(GLuint texture, GLuint activeTexture);
	bool AddTexture(const std::string& filename, GLuint activeTexture);

	void SetMaterial(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess);
	void SetTextures();

	static GLuint LoadTexture(const std::string& filename);

public:
	glm::vec3 ambient = glm::vec3(1.0f);
	glm::vec3 diffuse = glm::vec3(1.0f);
	glm::vec3 specular = glm::vec3(1.0f);
	float shininess = 100.0f;

	struct TextureInfo
	{
		GLenum type;
		GLuint activeTexture;
		GLuint texture;
	};

private:
	std::vector<TextureInfo> m_textures;
};