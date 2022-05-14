#include "lmxpch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace LMX
{

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		LMX_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;
		GLenum sourceColorChans;
		switch (channels)
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
		glCreateTextures(GL_TEXTURE_2D, 1, &ID);
		glTextureStorage2D(ID, 1, GL_RGB8, m_Width, m_Height);

		glTextureParameteri(ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(ID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		
		//glTextureParameteri(ID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glTextureParameteri(ID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTextureSubImage2D(ID, 0, 0, 0, m_Width, m_Height, sourceColorChans, GL_UNSIGNED_BYTE, data);
		glGenerateTextureMipmap(ID);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &ID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, ID);
	}
}