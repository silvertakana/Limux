#include "lmxpch.h"
#include "OpenGLTexture.h"
#include "Limux/Core/AssetLoader.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace LMX
{

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path, Settings setting)
	{
		LMX_PROFILE_FUNCTION();
		Load(path, setting);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		LMX_PROFILE_FUNCTION();
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		LMX_PROFILE_FUNCTION();
		glBindTextureUnit(slot, m_RendererID);
   	}
	void OpenGLTexture2D::Init()
	{
		if (!m_IsInit)
		{
			//stbi_set_flip_vertically_on_load(1);
			int channels;
			stbi_uc* data = stbi_load(m_Path.c_str(), &m_Width, &m_Height, &channels, 0);
			LMX_ASSERT(data, "Unable to load image with path: {0}", m_Path);

			switch (channels)
			{
			case 1:
				m_InternalFormat = GL_RED;
				break;
			case 4:
				m_InternalFormat = GL_RGBA;
				break;
			case 3:
			default:
				m_InternalFormat = GL_RGB;
				break;
			}
			glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);

			if (m_Setting & Red)
				glTextureStorage2D(m_RendererID, 1, GL_RED, m_Width, m_Height);
			else if (m_Setting & RGB)
				glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_Width, m_Height);
			else
				glTextureStorage2D(m_RendererID, 1, GL_RGBA8, m_Width, m_Height);



			if (m_Setting & Clamp)
			{
				glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}
			else if (m_Setting & Mirror)
			{
				glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
				glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
			}
			else // Repeat and unspecified
			{
				glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
			}

			if (m_Setting & MinLinear)
				glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			else
				glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			if (m_Setting & MagLinear)
				glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			else
				glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_InternalFormat, GL_UNSIGNED_BYTE, data);
			if (m_Setting & Mipmap)
				glGenerateTextureMipmap(m_RendererID);

			stbi_image_free(data);
			m_IsInit = true;
		}
	}
	
	void OpenGLTexture2D::Load(std::string filePath, Settings setting)
	{
		LMX_PROFILE_FUNCTION();

		m_Path = filePath;
		m_Setting = setting;
	}
}