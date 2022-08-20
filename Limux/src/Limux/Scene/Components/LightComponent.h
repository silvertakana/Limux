#pragma once
#include <glm/glm.hpp>
#include "Limux/Renderer/Shader.h"

#include "Limux/Scene/Scene.h"
#include "stdio.h"

namespace LMX
{
	struct LightComponent
	{
		
		class PointLight
		{
		public:
			PointLight() = default;
		};

		class SpotLight
		{
		public:
			float CutOff = 0.f, OuterCutOff = 0.f, RingIntensity = 0.f;
			SpotLight(float cutOff, float outerCutOff, const glm::vec3& color, float ringIntensity = 0) : CutOff(cutOff), OuterCutOff(outerCutOff), RingIntensity(ringIntensity) {}

			SpotLight() = default;
		};

		class DirecLight
		{
		public:
			DirecLight() = default;
		};


		
		enum class LightType : uint8_t
		{
			None,
			Point,
			Spot,
			Direc
		};
		union LightUnion
		{
			PointLight Point;
			SpotLight Spot{};
			DirecLight Direc;
			LightUnion() {}
			~LightUnion() {}
		};
		
		union LightUnion Instance;
		LightType Type = LightType::None;
		glm::vec3 Color{1.f};
		float Intensity = 1.f;
		bool Enabled = true;

		LightComponent() = default;
		LightComponent(const LightComponent&) = default;
		LightComponent(Scene*) {}
		LightComponent(Scene*, LightType type, glm::vec3 color, float intensity = 1.f) : Type(type), Color(color), Intensity(intensity) {}
	};
}