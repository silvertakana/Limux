#include "lmxpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace LMX
{

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}