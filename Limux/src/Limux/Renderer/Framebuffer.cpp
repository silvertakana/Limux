#include "lmxpch.h"
#include "Framebuffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace LMX
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		LMX_PROFILE_FUNCTION();
		Ref<Framebuffer> fb;
		LMX_SWITCHRENDERERAPI(
			fb.reset((Framebuffer*)new OpenGLFramebuffer(spec));
		);
		return fb;
	}
}