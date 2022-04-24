#include "lmxpch.h"

#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace LMX
{
	Camera::Camera(const float& newRatio)
	{
		ratio = newRatio;
	}

	void Camera::UpdateMatrix()
	{
		camMatrix = glm::perspective(fov, ratio, 0.1f, 100.0f);
		camMatrix *= glm::lookAt(position,
			position + direction,
			up);
	}

	void Camera::Control(const Window& window, float speed, float sensiv)
	{
		auto front = glm::normalize(direction);
		auto right = glm::normalize(glm::cross(front, up));
		auto forward = front;
		forward.y = 0.f;
		forward = glm::normalize(forward);
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			speed *= 5.f;

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			position += speed * forward;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			position -= speed * forward;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			position -= right * speed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			position += right * speed;
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			position -= speed * up;
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			position += speed * up;

		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
			fov += (glm::radians(20.f) - fov) * 0.3;
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_RELEASE)
			fov += (glm::radians(45.f) - fov) * 0.3;

		float rotationSpeed = 0.05f;

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			direction = glm::rotate(direction, rotationSpeed, right);
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			direction = glm::rotate(direction, -rotationSpeed, right);
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
			direction = glm::rotate(direction, rotationSpeed, up);
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
			direction = glm::rotate(direction, -rotationSpeed, up);


		// Handles mouse inputs
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			// Hides mouse cursor
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

			// Prevents camera from jumping on the first click
			if (firstClick)
			{
				glfwSetCursorPos(window, (window.prop.width / 2), (window.prop.height / 2));
				firstClick = false;
			}

			// Stores the coordinates of the cursor
			double mouseX;
			double mouseY;
			// Fetches the coordinates of the cursor
			glfwGetCursorPos(window, &mouseX, &mouseY);

			// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
			// and then "transforms" them into degrees 
			float rotX = sensiv * (float)(mouseY - (window.prop.height / 2)) / window.prop.height;
			float rotY = sensiv * (float)(mouseX - (window.prop.width / 2)) / window.prop.width;

			// Calculates upcoming vertical change in the direction
			glm::vec3 newOrientation = glm::rotate(direction, glm::radians(-rotX), glm::normalize(glm::cross(direction, up)));

			// Decides whether or not the next vertical direction is legal or not
			if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
			{
				direction = newOrientation;
			}

			// Rotates the direction left and right
			direction = glm::rotate(direction, glm::radians(-rotY), up);

			// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
			glfwSetCursorPos(window, (window.prop.width / 2), (window.prop.height / 2));
		}
		else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			// Unhides cursor since camera is not looking around anymore
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			// Makes sure the next time the camera looks around it doesn't jump
			firstClick = true;
		}
	}


	void Camera::Push(const Shader& shader, const char* name)
	{
		static const Shader* crntShader = nullptr;
		static GLuint MatrixID;
		if (&shader != crntShader)
		{
			crntShader = &shader;
		}
		MatrixID = crntShader->GetUni(name);
		crntShader->Use();
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, glm::value_ptr(camMatrix));
	}
}
