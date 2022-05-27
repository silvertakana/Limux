#include "lmxpch.h"
#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace LMX
{
	Texture2D* Texture2D::Load(const std::string& path, int setting)
	{
		SWITCHRENDERERAPI(
			return new OpenGLTexture2D(path, (Settings)setting);
		);
		return nullptr;
	}
}