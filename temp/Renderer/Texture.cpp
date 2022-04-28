#include "lmxpch.h"

#include "Texture.h"
#include <stb/stb_image.h>
#include <GLFW/glfw3.h>
namespace LMX
{
	static std::map<std::string, GLuint> texDict;
	Texture::Texture(const Texture& texture)
		:ID(texture.ID), type(texture.type)
	{}

	Texture::Texture(const std::string& filePath, Types type, bool flip, GLenum filt, GLenum wrap)
	{
		this->type = type;
		if (texDict.contains(filePath))
		{
			ID = texDict[filePath];
		}
		else
		{
			glCreateTextures(GL_TEXTURE_2D, 1, &ID);
			// load and generate the texture
			if (flip) stbi_set_flip_vertically_on_load(true);
			else stbi_set_flip_vertically_on_load(false);
			int width, height, colorChannels;
			unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &colorChannels, 4);
			if (data)
			{
				GLenum sourceColorChans;
				switch (colorChannels)
				{
				case 1:
					sourceColorChans = GL_RED;
					break;
				case 4:
					sourceColorChans = GL_RGBA;
					break;
				case 3:
				default:
					sourceColorChans = GL_RGB;
					break;
				}

				glTextureParameteri(ID, GL_TEXTURE_WRAP_S, wrap);
				glTextureParameteri(ID, GL_TEXTURE_WRAP_T, wrap);
				glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, filt);
				glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, filt);

				glTextureStorage2D(ID, 1, GL_RGBA8, width, height);
				glTextureSubImage2D(ID, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
				glGenerateTextureMipmap(ID);

				texDict[filePath] = ID;

				stbi_image_free(data);
			}
			else
			{
				ERROR("Unable to load image: {0}", filePath);
			}
			stbi_set_flip_vertically_on_load(false);
		}
	}

	void Texture::Param(GLenum pname, GLenum param)
	{
		glTextureParameteri(ID, pname, param);
	}

	void Texture::Bind(GLuint texUnit) const
	{
		glBindTextureUnit(texUnit, ID);
	}

	void Texture::UnBind(GLuint texUnit)
	{
		#ifdef _DEBUG
		static Texture DefaultTexture { "res/textures/missing_texture.png", Types::diffuse, false, GL_NEAREST };
		#else
		static Texture DefaultTexture { "res/textures/default.png", Types::diffuse, false, GL_NEAREST };
		#endif // DEBUG

		glBindTextureUnit(texUnit, DefaultTexture);
	}
}