#include "lmxpch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace LMX
{

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		LMX_PROFILE_FUNCTION();
		LMX_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		LMX_PROFILE_FUNCTION();
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		LMX_ASSERT(status, "Failed to initialize Glad!");

		#ifdef LMX_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		LMX_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Limux requires at least OpenGL version 4.5!");
		#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		LMX_PROFILE_FUNCTION();
		glfwSwapBuffers(m_WindowHandle);
	}

}