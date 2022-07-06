#pragma once
#include "Limux/Renderer/Texture.h"
namespace LMX
{
	class OpenGLTexture2D : public Texture2D
	{
	protected:
		uint32_t m_RendererID = 0; 
	public:
		OpenGLTexture2D(const std::string& path, Settings setting);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override  { return m_Width ; }
		virtual uint32_t GetHeight() const override { return m_Height; }
		virtual uint32_t GetRendererID() const override { return m_RendererID; }

		virtual void Bind(uint32_t slot = 0) const override;
	private:
		int m_Width, m_Height;
		Settings m_Setting;
		int m_InternalFormat;
	private:
		virtual void Init() override;
		virtual void Load(std::string filePath, Settings setting);
	};
}