#include "lmxpch.h"
#include "Limux/Core/Input.h"

#include "Limux/Core/Application.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace LMX
{
	bool Input::IsKeyPressed(KeyCode key)
	{
		LMX_PROFILE_FUNCTION();
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, static_cast<int32_t>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(MouseCode button)
	{
		LMX_PROFILE_FUNCTION();
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		LMX_PROFILE_FUNCTION();
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float Input::GetMouseX()
	{
		LMX_PROFILE_FUNCTION();
		auto [x, y] = GetMousePosition();
		return x;
	}

	float Input::GetMouseY()
	{
		LMX_PROFILE_FUNCTION();
		auto [x, y] = GetMousePosition();
		return y;
	}

	std::pair<float, float> Input::SetMousePosition(float x, float y)
	{
		LMX_PROFILE_FUNCTION();
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		glfwSetCursorPos(window, x, y);
		return {x,y};
	}

	float Input::SetMouseX(float x)
	{
		LMX_PROFILE_FUNCTION();
		auto [oldX, oldY] = GetMousePosition();
		return SetMousePosition(x, oldY).first;
	}

	float Input::SetMouseY(float y)
	{
		LMX_PROFILE_FUNCTION();
		auto [oldX, oldY] = GetMousePosition();
		return SetMousePosition(oldX, y).second;
	}

	void Input::SetInputMode(InputType inptype, InputMode mode)
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