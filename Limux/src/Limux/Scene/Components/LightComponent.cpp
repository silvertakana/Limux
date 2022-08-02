#include "lmxpch.h"
#include "LightComponent.h"

namespace LMX
{

	//void SpotLight::Push(std::string name, Ref<Shader> shader) const
	//{
	//	Light::Push(name, shader);
	//	constexpr auto stringJoiner = "{0}.{1}";
	//	shader->SetUniform(std::format(stringJoiner, name, "position"), position);
	//	shader->SetUniform(std::format(stringJoiner, name, "direction"), direction);
	//	shader->SetUniform(std::format(stringJoiner, name, "cutOff"), cutOff);
	//	shader->SetUniform(std::format(stringJoiner, name, "outerCutOff"), outerCutOff);
	//	shader->SetUniform(std::format(stringJoiner, name, "ringIntensity"), ringIntensity);
	//}


	//void LightComponent::Push(std::string name, Ref<Shader> shader) const
	//{
	//	LMX_PROFILE_FUNCTION();
	//	LMX_ASSERT(Instance, "LightComponent is not initialized");
	//	
	//	constexpr auto stringJoiner = "{0}.{1}";
	//	shader->SetUniform(std::format(stringJoiner, name, "Color"), Color());
	//	shader->SetUniform(std::format(stringJoiner, name, "Enabled"), Enabled());
	//}
}