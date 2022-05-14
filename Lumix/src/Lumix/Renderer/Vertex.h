#pragma once
#include <glm/glm.hpp>
namespace LMX
{
	struct Vertex
	{
		glm::vec3 pos;
		glm::vec4 color;
		glm::vec2 texCoord;
		//glm::vec3 normal;
	};
}