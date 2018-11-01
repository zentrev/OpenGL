#include "material.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void Material::SetMaterial(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular, float shininess)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
}

void Material::AddTexture(GLuint textureID, GLuint activeTexture)
{
	TextureInfo textureInfo = { GL_TEXTURE_2D, activeTexture, textureID };
	m_textures.push_back(textureInfo);
}

bool Material::AddTexture(const std::string& filename, GLuint activeTexture)
{
	GLuint textureID = LoadTexture(filename);
	if (textureID != 0)
	{
		TextureInfo textureInfo = { GL_TEXTURE_2D, activeTexture, textureID };
		m_textures.push_back(textureInfo);
	}

	return (textureID != 0);
}

void Material::SetTextures()
{
	for (TextureInfo textureInfo : m_textures)
	{
		glActiveTexture(textureInfo.activeTexture);
		glBindTexture(textureInfo.type, textureInfo.texture);
	}
}

GLuint Material::LoadTexture(const std::string& filename)
{
	GLuint textureID = 0;

	int width;
	int height;
	int n;

	SDL_Log("Loading Texture <%s>", filename.c_str());

	stbi_set_flip_vertically_on_load(true);
	unsigned char* image = stbi_load(filename.c_str(), &width, &height, &n, 0);

	if (image == nullptr)
	{
		SDL_Log("Error: Could not load texture <%s>", filename.c_str());
	}
	
	if (image)
	{
		SDL_Log("Success");

		GLenum storageFormat = (n == 4) ? GL_RGBA8 : GL_RGB8;
		GLenum imageFormat = (n == 4) ? GL_RGBA : GL_RGB;
				
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexStorage2D(GL_TEXTURE_2D, 1, storageFormat, width, height);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, imageFormat, GL_UNSIGNED_BYTE, image);

		stbi_image_free(image);
	}

	return textureID;
}
