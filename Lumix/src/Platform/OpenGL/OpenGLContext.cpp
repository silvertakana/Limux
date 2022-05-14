#include "lmxpch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace LMX
{

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		LMX_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		LMX_ASSERT(status, "Failed to initialize Glad!");

		LMX_INFO("OpenGL Info:");
		LMX_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		LMX_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		LMX_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}