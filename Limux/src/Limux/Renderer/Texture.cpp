#include "lmxpch.h"
#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace LMX
{
	Ref<Texture2D> Texture2D::Load(const std::string& path, int setting)
	{
		LMX_PROFILE_FUNCTION();
		LMX_SWITCHRENDERERAPI(
			return CreateRef<OpenGLTexture2D>(path, (Settings)setting);
		);
		return nullptr;
	}
}