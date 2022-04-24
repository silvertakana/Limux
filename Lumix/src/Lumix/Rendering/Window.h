#pragma once
#include<glad/glad.h>
#include<GLFW/glfw3.h>
namespace LMX
{
	class Window
	{
	public:
		GLFWwindow* GLwindow;
		struct Prop
		{
			size_t width = 600, height = 600;
			const char* name = "Window";
		};
		Prop prop;
		Window(const Prop& prop, const int& versionMajor = 4, const int& versionMinor = 6, const int& profile = GLFW_OPENGL_CORE_PROFILE);
		~Window();
		operator GLFWwindow* () const
		{
			return GLwindow;
		};
	};
}


