#pragma once
#include <glm/glm.hpp>
#include "Limux/Core/Core.h"

namespace LMX
{
	class UniformSetter;
	class Shader
	{
	public:
		static Ref<Shader> Create(const std::string &fileSrc);
		static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc);
		
		static Ref<Shader> Load(const std::string& filePath);
		static Ref<Shader> Load(const std::string& vertexPath, const std::string& fragmentPath);
		template<class T>
		UniformSetter SetUniform(const std::string& identifier, const T& data)
		{
			LMX_PROFILE_FUNCTION();
			return operator[](identifier) = data;
		}
		UniformSetter operator[](const std::string& identifier);
		virtual ~Shader() = default;
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
	};
	
	class UniformSetter
	{
		Shader& m_Shader;
		std::string m_Identifier;
	public:
		UniformSetter(Shader& shader, const std::string& identifier)
			:m_Shader(shader), m_Identifier(identifier)
		{}
		void operator=(const bool& data);
		void operator=(const int& data);
		void operator=(const float& data);
		void operator=(const glm::vec2& data);
		void operator=(const glm::vec3& data);
		void operator=(const glm::vec4& data);
		void operator=(const glm::mat2& data);
		void operator=(const glm::mat3& data);
		void operator=(const glm::mat4& data);

	};
}