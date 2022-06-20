#include "lmxpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace LMX
{
	void OpenGLMessageCallback(
		GLenum source,
		GLenum type,
		unsigned int id,
		GLenum severity,
		GLsizei length,
		const char* message,
		const void* userParam)
	{
		// ignore non-significant error/warning codes
		//if (id == 131169 || id == 131185 || id == 131218 || id == 131204 || id == 1282) return;
		std::string errorMessage = std::format("[{0}]: {1}\n", id, message);
		switch (source)
		{
		case GL_DEBUG_SOURCE_API:             errorMessage += "Source: API"; break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   errorMessage += "Source: Window System"; break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER: errorMessage += "Source: Shader Compiler"; break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:     errorMessage += "Source: Third Party"; break;
		case GL_DEBUG_SOURCE_APPLICATION:     errorMessage += "Source: Application"; break;
		case GL_DEBUG_SOURCE_OTHER:           errorMessage += "Source: Other"; break;
		}
		errorMessage += "\n";

		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR:               errorMessage += "Type: Error"; break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: errorMessage += "Type: Deprecated Behaviour"; break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  errorMessage += "Type: Undefined Behaviour"; break;
		case GL_DEBUG_TYPE_PORTABILITY:         errorMessage += "Type: Portability"; break;
		case GL_DEBUG_TYPE_PERFORMANCE:         errorMessage += "Type: Performance"; break;
		case GL_DEBUG_TYPE_MARKER:              errorMessage += "Type: Marker"; break;
		case GL_DEBUG_TYPE_PUSH_GROUP:          errorMessage += "Type: Push Group"; break;
		case GL_DEBUG_TYPE_POP_GROUP:           errorMessage += "Type: Pop Group"; break;
		case GL_DEBUG_TYPE_OTHER:               errorMessage += "Type: Other"; break;
		}

		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         LMX_ASSERT(false, "{0}", errorMessage); break; // check console for error messages
		case GL_DEBUG_SEVERITY_MEDIUM:       LMX_ERROR ("{0}", errorMessage);		 break;
		case GL_DEBUG_SEVERITY_LOW:          LMX_WARN  ("{0}", errorMessage);		 break;
		case GL_DEBUG_SEVERITY_NOTIFICATION: LMX_INFO  ("{0}", errorMessage);		 break;
		}
	}
	
	void OpenGLRendererAPI::Init()
	{
		LMX_PROFILE_FUNCTION();

		#ifdef LMX_DEBUG
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(OpenGLMessageCallback, nullptr);

			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
		#endif
		
		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
		//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
		glEnable(GL_DEPTH_TEST);
	}
	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		LMX_PROFILE_FUNCTION();
		glViewport(x, y, width, height);
	}
	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		LMX_PROFILE_FUNCTION();
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		LMX_PROFILE_FUNCTION();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	float OpenGLRendererAPI::GetTime()
	{
		LMX_PROFILE_FUNCTION();
		return (float)glfwGetTime();
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		LMX_PROFILE_FUNCTION();
		vertexArray->Bind();
		glDrawElements(GL_TRIANGLES, vertexArray->GetEBO()->GetSize() / sizeof(uint32_t), GL_UNSIGNED_INT, nullptr);
		vertexArray->UnBind();
	}

}