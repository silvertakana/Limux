#pragma once
#include "Limux/Core/Base.h"
#include "glm/glm.hpp"
#include "Shader.h"
namespace LMX
{
	class Texture
	{
	protected:
		std::string m_Path;
		bool m_IsInit = false;
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
		virtual uint32_t GetRendererID() const = 0;

		virtual void Init() = 0;
		virtual std::string  GetPath() const = 0;
		virtual std::string& GetPath()		 = 0;
		virtual void Bind(uint32_t slot = 0) const = 0;
		static std::map<std::string, Ref<Texture>> loadedTextures;
	};

	class Texture2D : public Texture
	{
	public:
		enum Settings
		{
			MinLinear	= BIT(0),
			MagLinear	= BIT(1),
			Clamp		= BIT(2),
			Mirror		= BIT(3),
			Mipmap		= BIT(4),
			Red			= BIT(5),
			RGB			= BIT(6),
		};
		enum TextureType
		{
			Auto,
			Any,
			Ambient,
			Diffuse,
			Specular,
			Roughness,
			Normal,
			Metallic,
			Height,
		};
		virtual void Uniform(Ref<Shader> shader, std::string identifier, uint32_t slot = 0) const;
		virtual bool IsSingleColor() const = 0;
		static std::string TextureTypeToString(TextureType type);
		TextureType type;
		static Ref<Texture2D> Load(const  std::string& path, TextureType type = Auto, int setting = LMX::Texture2D::Mipmap | LMX::Texture2D::MagLinear);
		static Ref<Texture2D> Load(			glm::vec4 color, TextureType type = Auto, int setting = LMX::Texture2D::Mipmap | LMX::Texture2D::MagLinear);
		virtual void Reload(const std::string& path, TextureType type = Auto, int setting = LMX::Texture2D::Mipmap | LMX::Texture2D::MagLinear) = 0;
		virtual void Reload(		glm::vec4 color, TextureType type = Auto, int setting = LMX::Texture2D::Mipmap | LMX::Texture2D::MagLinear) = 0;
		static void SetDefaultTexture(const std::string& path, TextureType type = Auto, int setting = LMX::Texture2D::Mipmap | LMX::Texture2D::MagLinear);
	};
}

