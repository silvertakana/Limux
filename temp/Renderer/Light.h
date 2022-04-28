#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "Shader.h"
namespace LMX
{
	class Light
	{
	public:
		glm::vec3 color;
		bool on = true;
		Light(const glm::vec3& color, bool on = true) :color(color), on(on) {}
		Light() :color(0.f) {}
		virtual void Push(std::string name, const Shader& shader) const;
	};

	class PointLight : public Light
	{
	public:
		glm::vec3 position;
		PointLight(const glm::vec3& position, const glm::vec3& color) :position(position), Light(color) {}
		PointLight() :Light(), position(0.f) {}
		void Push(std::string name, const Shader& shader) const override;
	};

	class SpotLight : public Light
	{
	public:
		glm::vec3 position, direction;
		float cutOff, outerCutOff, ringIntensity = 0;
		SpotLight(const glm::vec3& position, const glm::vec3& direction, float cutOff, float outerCutOff, const glm::vec3& color, float ringIntensity = 0) :position(position), direction(direction), cutOff(cutOff), outerCutOff(outerCutOff), Light(color), ringIntensity(ringIntensity) {}
		SpotLight() :Light(), position(0.f), direction(0.f), cutOff(0.f), outerCutOff(0.f) {}
		void Push(std::string name, const Shader& shader) const override;
	};

	class DirecLight : public Light
	{
	public:
		glm::vec3 direction;
		DirecLight(const glm::vec3& direction, const glm::vec3& color) :direction(direction), Light(color) {}
		DirecLight() :Light(), direction(0.f) {}
		void Push(std::string name, const Shader& shader) const override;
	};
}