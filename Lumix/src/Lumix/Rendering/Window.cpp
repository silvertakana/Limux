#include "lmxpch.h"

#include "Window.h"
#include "Lumix/Log.h"

void APIENTRY glDebugOutput(GLenum source,
	GLenum type,
	unsigned int id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam)
{
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;
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
	case GL_DEBUG_SEVERITY_HIGH:         LMX_CRITIC(errorMessage); __debugbreak(); break;
	case GL_DEBUG_SEVERITY_MEDIUM:       LMX_ERROR(errorMessage); __debugbreak();  break;
	case GL_DEBUG_SEVERITY_LOW:          LMX_WARN(errorMessage);   break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: LMX_INFO(errorMessage);   break;
	}
}
namespace LMX
{
	Window::Window(const Prop& prop, const int& versionMajor, const int& versionMinor, const int& profile)
	{
		static bool glfwInited = false;
		this->prop = prop;
		// Initialize GLFW
		if (!glfwInited) { glfwInit(); glfwInited = true; }
		// Tell GLFW what version of OpenGL we are using 
		// In this case we are using OpenGL 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
		// Tell GLFW we are using the CORE profile
		// So that means we only have the modern functions
		glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
		GLwindow = glfwCreateWindow(prop.width, prop.height, prop.name, NULL, NULL);

		if (GLwindow == NULL)
		{
			printf("Failed to create GLFW window\n");
			glfwTerminate();
			exit(EXIT_FAILURE);
		}
		// Introduce the window into the current context
		glfwMakeContextCurrent(GLwindow);
		//Load GLAD so it configures OpenGL
		if (!gladLoadGL())
		{
			printf("Failed to initialize GLAD\n");
			glfwTerminate();
			exit(EXIT_FAILURE);
		}
		int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(glDebugOutput, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}

		// Specify the viewport of OpenGL in the Window
		// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
		glViewport(0, 0, prop.width, prop.height);
		auto framebuffer_size_callback = [](GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
			//Log::Info("WindowResize: {0}, {1}", width, height);
		};
		glfwSetFramebufferSizeCallback(GLwindow, framebuffer_size_callback);
		auto error_callback = [](int code, const char* message)
		{
			ERROR("[{0}]: {1}", code, message);
		};
		glfwSetErrorCallback(error_callback);
	}
	Window::~Window()
	{
		glfwDestroyWindow(GLwindow);
	}
}