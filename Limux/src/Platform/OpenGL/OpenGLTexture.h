#pragma once
#include "Limux/Renderer/Texture.h"
#include "glm/glm.hpp"
namespace LMX
{
	class OpenGLTexture2D : public Texture2D
	{
	protected:
		uint32_t m_RendererID = 0; 
	public:
		OpenGLTexture2D(const std::string& path, Settings setting);
		OpenGLTexture2D(glm::vec4 color, Settings setting);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override  { return m_Width ; }
		virtual uint32_t GetHeight() const override { return m_Height; }
		virtual void Reload(const std::string& path, TextureType type = Auto, int setting = LMX::Texture2D::Mipmap | LMX::Texture2D::MagLinear) override;
		virtual void Reload(		glm::vec4 color, TextureType type = Auto, int setting = LMX::Texture2D::Mipmap | LMX::Texture2D::MagLinear) override;
		virtual uint32_t GetRendererID() const override { return m_RendererID; }

		
		virtual std::string  GetPath() const override { return m_Path; }
		virtual std::string& GetPath()		 override { return m_Path; }
		virtual bool IsSingleColor() const override { return m_IsSingleColor; }
		virtual void Bind(uint32_t slot = 0) const override;
	private:
		int m_Width, m_Height;
		Settings m_Setting;
		bool m_IsSingleColor = false;
		glm::vec4 m_SingleColor;
		int m_InternalFormat;
	private:
		virtual void Init() override;
		virtual void Load(std::string filePath, Settings setting);
	};
}