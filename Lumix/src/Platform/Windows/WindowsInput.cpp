#include "lmxpch.h"
#include "WindowsInput.h"

#include "Lumix/Core/Application.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace LMX
{

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}

	std::pair<float, float> WindowsInput::SetMousePositionImpl(float x, float y)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		glfwSetCursorPos(window, x, y);
		return {x,y};
	}

	float WindowsInput::SetMouseXImpl(float x)
	{
		auto [oldX, oldY] = GetMousePositionImpl();
		return SetMousePositionImpl(x, oldY).first;
	}

	float WindowsInput::SetMouseYImpl(float y)
	{
		auto [oldX, oldY] = GetMousePositionImpl();
		return SetMousePositionImpl(oldX, y).second;
	}

	void WindowsInput::SetInputModeImpl(InputType inptype, InputMode mode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int glfwmode = GLFW_CURSOR_NORMAL;
		switch (mode)
		{
		case InputMode::CURSOR_NORMAL:
			glfwmode = GLFW_CURSOR_NORMAL;
			break;
		case InputMode::CURSOR_HIDDEN:
			glfwmode = GLFW_CURSOR_HIDDEN;
			break;
		case InputMode::CURSOR_DISABLED:
			glfwmode = GLFW_CURSOR_DISABLED;
			break;
		}
		switch (inptype)
		{
		case InputType::CURSOR:
			glfwSetInputMode(window, GLFW_CURSOR, glfwmode);
			break;
		}
	}
}