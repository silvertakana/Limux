#pragma once
#include <glm/glm.hpp>
#include "Lumix/Renderer/Shader.h"
namespace LMX
{
	class OpenGLShader : public Shader
	{
	public:
		uint32_t ID;
		OpenGLShader(const std::string & vertexSrc, const std::string & fragmentSrc);
		OpenGLShader(const std::string & shaderPath);
		virtual ~OpenGLShader();
		
		virtual void Bind() const;
		virtual void Unbind() const;

		uint32_t GetUni(const std::string& name) const;

		uint32_t setBool (const std::string& name, bool    value) const;
		uint32_t setInt  (const std::string& name, int     value) const;
		uint32_t setFloat(const std::string& name, float   value) const;
		uint32_t setVec2 (const std::string& name, glm::vec2 vec) const;
		uint32_t setVec3 (const std::string& name, glm::vec3 vec) const;
		uint32_t setVec4 (const std::string& name, glm::vec4 vec) const;
		uint32_t setMat2 (const std::string& name, glm::mat2 mat) const;
		uint32_t setMat3 (const std::string& name, glm::mat3 mat) const;
		uint32_t setMat4 (const std::string& name, glm::mat4 mat) const;

		uint32_t setBool (uint32_t loc, bool    value) const;
		uint32_t setInt  (uint32_t loc, int     value) const;
		uint32_t setFloat(uint32_t loc, float   value) const;
		uint32_t setVec2 (uint32_t loc, glm::vec2 vec) const;
		uint32_t setVec3 (uint32_t loc, glm::vec3 vec) const;
		uint32_t setVec4 (uint32_t loc, glm::vec4 vec) const;
		uint32_t setMat2 (uint32_t loc, glm::mat2 mat) const;
		uint32_t setMat3 (uint32_t loc, glm::mat3 mat) const;
		uint32_t setMat4 (uint32_t loc, glm::mat4 mat) const;

	};
}

