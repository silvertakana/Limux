#pragma once
#include <glm/glm.hpp>
#include "Limux/Renderer/Shader.h"

#include "Limux/Scene/Scene.h"

namespace LMX
{
	struct LightComponent
	{
		class Light
		{
		public:
			
			Light() {}
			enum class LightTypes : uint8_t
			{
				None		= -1,
				PointLight	=  0,
				SpotLight	=  1,
				DirecLight	=  2,
			};
			virtual LightTypes constexpr GetType() const { return LightTypes::None; }
		};

		class PointLight : public Light
		{
		public:
			PointLight() {}
			virtual LightTypes constexpr GetType() const override { return LightTypes::PointLight; }
		};

		class SpotLight : public Light
		{
		public:
			float CutOff = 0.f, OuterCutOff = 0.f, RingIntensity = 0.f;
			SpotLight(float cutOff, float outerCutOff, const glm::vec3& color, float ringIntensity = 0) : CutOff(cutOff), OuterCutOff(outerCutOff), RingIntensity(ringIntensity) {}

			SpotLight() {}
			virtual LightTypes constexpr GetType() const override { return LightTypes::SpotLight; }
		};

		class DirecLight : public Light
		{
		public:
			DirecLight() {}
			virtual LightTypes constexpr GetType() const override { return LightTypes::DirecLight; }
		};
		
		Ref<Light> Instance = nullptr;
		
		glm::vec3 Color;
		float Intensity = 1.f;
		bool Enabled = true;

		LightComponent() = default;
		LightComponent(const LightComponent&) = default;
		LightComponent(Scene*) {}
		LightComponent(Scene*,     Light* light, glm::vec3 color, float intensity = 1.f) : Instance(light), Color(color), Intensity(intensity) {}
		LightComponent(Scene*, Ref<Light> light, glm::vec3 color, float intensity = 1.f) : Instance(light), Color(color), Intensity(intensity) {}
		
		Light::LightTypes GetType() const { return Instance->GetType(); }
	};
}