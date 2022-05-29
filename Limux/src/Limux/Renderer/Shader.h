#pragma once
#include <glm/glm.hpp>
#include "Limux/Core/Core.h"

namespace LMX
{
	class Shader
	{
	public:
		static Ref<Shader> Create(const std::string &fileSrc);
		static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
		
		static Ref<Shader> Load(const std::string& filePath);
		static Ref<Shader> Load(const std::string& vertexPath, const std::string& fragmentPath);
		virtual ~Shader() = default;
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		uint32_t setBool (const std::string& name, bool    value) const;
		uint32_t setInt  (const std::string& name, int     value) const;
		uint32_t setFloat(const std::string& name, float   value) const;
		uint32_t setVec2 (const std::string& name, glm::vec2 vec) const;
		uint32_t setVec3 (const std::string& name, glm::vec3 vec) const;
		uint32_t setVec4 (const std::string& name, glm::vec4 vec) const;
		uint32_t setMat2 (const std::string& name, glm::mat2 mat) const;
		uint32_t setMat3 (const std::string& name, glm::mat3 mat) const;
		uint32_t setMat4 (const std::string& name, glm::mat4 mat) const;
	};
}