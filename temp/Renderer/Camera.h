#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

namespace LMX
{
	class Camera
	{
		bool firstClick = false;
	public:
		glm::vec3 position { 0.f }, direction { 0.f,0.f,-1.f }, up { 0.f, 1.f, 0.f };
		glm::mat4 camMatrix { 1.f };
		float ratio = 1.f, fov = glm::radians(45.f);
		Camera(const float& newRatio);
		void UpdateMatrix();
		void Control(GLFWwindow* window, float speed, float sensiv);
		void Push(const Shader& shader, const char* name = "uCameraMatrix");
	};
}