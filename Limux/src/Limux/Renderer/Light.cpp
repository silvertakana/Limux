#include "lmxpch.h"
#include "Light.h"

namespace LMX
{
	void Light::Push(std::string name, Ref<Shader> shader) const
	{
		constexpr auto stringJoiner = "{0}.props.{1}";
		shader->SetUniform(std::format(stringJoiner, name, "color"), color);
		shader->SetUniform(std::format(stringJoiner, name, "on"), on);
	}

	void PointLight::Push(std::string name, Ref<Shader> shader) const
	{
		Light::Push(name, shader);
		constexpr auto stringJoiner = "{0}.{1}";
		shader->SetUniform(std::format(stringJoiner, name, "position"), position);
	}

	void SpotLight::Push(std::string name, Ref<Shader> shader) const
	{
		Light::Push(name, shader);
		constexpr auto stringJoiner = "{0}.{1}";
		shader->SetUniform(std::format(stringJoiner, name, "position"), position);
		shader->SetUniform(std::format(stringJoiner, name, "direction"), direction);
		shader->SetUniform(std::format(stringJoiner, name, "cutOff"), cutOff);
		shader->SetUniform(std::format(stringJoiner, name, "outerCutOff"), outerCutOff);
		shader->SetUniform(std::format(stringJoiner, name, "ringIntensity"), ringIntensity);
	}

	void DirecLight::Push(std::string name, Ref<Shader> shader) const
	{
		Light::Push(name, shader);
		constexpr auto stringJoiner = "{0}.{1}";
		shader->SetUniform(std::format(stringJoiner, name, "direction"), direction);
	}

}