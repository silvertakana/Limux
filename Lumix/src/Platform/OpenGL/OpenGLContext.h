#pragma once

#include "Lumix/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace LMX
{

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}