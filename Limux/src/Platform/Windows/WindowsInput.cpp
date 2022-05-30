#include "lmxpch.h"
#include "WindowsInput.h"

#include "Limux/Core/Application.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace LMX
{

	Scope<Input> Input::s_Instance = CreateScope<WindowsInput>();

	bool WindowsInput::IsKeyPressedImpl(KeyCode key)
	{
		LMX_PROFILE_FUNCTION();
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, static_cast<int32_t>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(MouseCode button)
	{
		LMX_PROFILE_FUNCTION();
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		LMX_PROFILE_FUNCTION();
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		LMX_PROFILE_FUNCTION();
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		LMX_PROFILE_FUNCTION();
		auto [x, y] = GetMousePositionImpl();
		return y;
	}

	std::pair<float, float> WindowsInput::SetMousePositionImpl(float x, float y)
	{
		LMX_PROFILE_FUNCTION();
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		glfwSetCursorPos(window, x, y);
		return {x,y};
	}

	float WindowsInput::SetMouseXImpl(float x)
	{
		LMX_PROFILE_FUNCTION();
		auto [oldX, oldY] = GetMousePositionImpl();
		return SetMousePositionImpl(x, oldY).first;
	}

	float WindowsInput::SetMouseYImpl(float y)
	{
		LMX_PROFILE_FUNCTION();
		auto [oldX, oldY] = GetMousePositionImpl();
		return SetMousePositionImpl(oldX, y).second;
	}

	void WindowsInput::SetInputModeImpl(InputType inptype, InputMode mode)
	{
		LMX_PROFILE_FUNCTION();
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