#pragma once
#include "Lumix/Renderer/Texture.h"
namespace LMX
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		uint32_t ID = 0;
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void Bind(uint32_t slot = 0) const override;
	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
	};
}