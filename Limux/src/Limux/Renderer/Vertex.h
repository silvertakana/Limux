#pragma once
#include <glm/glm.hpp>
namespace LMX
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoord;
		glm::vec4 Color;
	};
}