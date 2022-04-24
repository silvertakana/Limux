#include "lmxpch.h"
#include "Light.h"

namespace LMX
{
	void Light::Push(const char* name, const Shader& shader) const
	{
		const char* stringJoiner = "{0}.props.{1}";
		shader.setVec3(std::format(stringJoiner, name, "color"), color);
		shader.setBool(std::format(stringJoiner, name, "on"), on);
	}

	void PointLight::Push(const char* name, const Shader& shader) const
	{
		Light::Push(name, shader);
		const char* stringJoiner = "{0}.{1}";
		shader.setVec3(std::format(stringJoiner, name, "position"), position);
	}

	void SpotLight::Push(const char* name, const Shader& shader) const
	{
		Light::Push(name, shader);
		const char* stringJoiner = "{0}.{1}";
		shader.setVec3(std::format(stringJoiner, name, "position"), position);
		shader.setVec3(std::format(stringJoiner, name, "direction"), direction);
		shader.setFloat(std::format(stringJoiner, name, "cutOff"), cutOff);
		shader.setFloat(std::format(stringJoiner, name, "outerCutOff"), outerCutOff);
		shader.setFloat(std::format(stringJoiner, name, "ringIntensity"), ringIntensity);
	}

	void DirecLight::Push(const char* name, const Shader& shader) const
	{
		Light::Push(name, shader);
		const char* stringJoiner = "{0}.{1}";
		shader.setVec3(std::format(stringJoiner, name, "direction"), direction);
	}

}