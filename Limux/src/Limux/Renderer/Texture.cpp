#include "lmxpch.h"
#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace LMX
{
	std::string Texture2D::TextureTypeToString(TextureType type)
	{
		std::string result;
		switch (type)
		{
		case TextureType::Diffuse:
			result = "diffuse";
			break;
		case TextureType::Specular:
			result = "specular";
			break;
		case TextureType::Roughness:
			result = "roughness";
			break;
		case TextureType::Normal:
			result = "normal";
			break;
		case TextureType::Metallic:
			result = "cubemap";
			break;
		case TextureType::Height:
			result = "height";
			break;
		default:
			result = "any";
			break;
		};
					
		return result;
	}
	Texture2D::TextureType AutoType(std::string path)
	{
		std::transform(path.begin(), path.end(), path.begin(), ::tolower); // lower case the string
		
		std::map<Texture2D::TextureType, std::vector<std::string>> typemapper;
		typemapper[Texture2D::Diffuse] = { "diffuse", "albedo", "base" };
		typemapper[Texture2D::Specular] = { "spec", "reflection"};
		typemapper[Texture2D::Roughness] = { "rough", "gloss" };
		typemapper[Texture2D::Normal] = { "normal", "bump" };
		typemapper[Texture2D::Metallic] = { "metal"};
		typemapper[Texture2D::Height] = { "height", "displace"};
		
		for (auto& pair : typemapper)
		{
			for (auto& ext : pair.second)
			{
				if (path.contains(ext))
				{
					return pair.first;
				}
			}
		}
	}
	std::map<std::string, Ref<Texture>> Texture::loadedTextures = {};
	Ref<Texture2D> Texture2D::Load(const std::string& path, TextureType type, int setting)
	{
		LMX_PROFILE_FUNCTION();
		Ref<Texture2D> texture = nullptr;
		
		if (loadedTextures.contains(path))
		{
			return std::static_pointer_cast<Texture2D>(loadedTextures[path]);
		}
		
		LMX_SWITCHRENDERERAPI(
			texture = CreateRef<OpenGLTexture2D>(path, (Settings)setting);
		);
		
		if (type == Auto)
			texture->type = AutoType(path);
		else
			texture->type = type;

		loadedTextures[path] = texture;
		return texture;
	}
	void Texture2D::SetDefaultTexture(const std::string& path, TextureType type, int setting)
	{
		LMX_PROFILE_FUNCTION();
		Ref<Texture2D> texture = Load(path, type, setting);
		texture->Init();
		texture->Bind();
	}
}