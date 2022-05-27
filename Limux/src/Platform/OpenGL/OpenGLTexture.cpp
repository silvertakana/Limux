#include "lmxpch.h"
#include "OpenGLTexture.h"
#include "Limux/Core/AssetLoader.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace LMX
{

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path, Settings setting)
		: m_Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		LMX_ASSERT(data, "Unable to load image with path: {0}", path);
		Load(data, width, height, channels, setting);
	}

	OpenGLTexture2D::OpenGLTexture2D(const uint8_t* buffer, size_t size, Settings setting)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load_from_memory(buffer, size, &width, &height, &channels, 0);
		Load(data, width, height, channels, setting);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &ID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, ID);
	}
	void OpenGLTexture2D::Load(uint8_t* data, int width, int height, int channels, Settings setting)
	{
		
		LMX_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;
		GLenum internalFormat;
		switch (channels)
		{
		case 1:
			internalFormat = GL_RED;
			break;
		case 4:
			internalFormat = GL_RGBA;
			break;
		case 3:
		default:
			internalFormat = GL_RGB;
			break;
		}
		glCreateTextures(GL_TEXTURE_2D, 1, &ID);
		
		if      (setting & Red) glTextureStorage2D(ID, 1, GL_RED, m_Width, m_Height);
		else if (setting & RGB) glTextureStorage2D(ID, 1, GL_RGB8, m_Width, m_Height);
		else                    glTextureStorage2D(ID, 1, GL_RGBA8, m_Width, m_Height);
		
		
		
		if(setting & Clamp)
		{
			glTextureParameteri(ID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTextureParameteri(ID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}
		else if (setting & Mirror)
		{
			glTextureParameteri(ID, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTextureParameteri(ID, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		}else // Repeat and unspecified
		{
			glTextureParameteri(ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(ID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		}
		
		if (setting & MinLinear) glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		else					 glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		
		if (setting & MagLinear) glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		else					 glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(ID, 0, 0, 0, m_Width, m_Height, internalFormat, GL_UNSIGNED_BYTE, data);
		if (setting & Mipmap) glGenerateTextureMipmap(ID);

		stbi_image_free(data);
	}
}