#pragma once
#include <glm/glm.hpp>
#include <Limux/Core/Core.h>
#include "Limux/Renderer/Shader.h"
#include "OpenGLTexture.h"
namespace LMX
{
	class OpenGLShader : public Shader
	{
	public:
		uint32_t ID;
		OpenGLShader(const std::string & vertexSrc, const std::string & fragmentSrc);
		OpenGLShader(const std::string & shaderSrc);
		static Ref<OpenGLShader> Load(const std::string& shaderPath);
		static Ref<OpenGLShader> Load(const std::string& vertexPath, const std::string& fragmentPath);
		virtual ~OpenGLShader();
		
		virtual void Bind() const;
		virtual void Unbind() const;
		void operator [](std::string uniformName)
		{
			
		}

		uint32_t GetUni(const std::string& name) const;

		uint32_t setUniform(const std::string& name, bool    value) const;
		uint32_t setUniform(const std::string& name, int     value) const;
		uint32_t setUniform(const std::string& name, float   value) const;
		uint32_t setUniform(const std::string& name, const glm::vec2& vec) const;
		uint32_t setUniform(const std::string& name, const glm::vec3& vec) const;
		uint32_t setUniform(const std::string& name, const glm::vec4& vec) const;
		uint32_t setUniform(const std::string& name, const glm::mat2& mat) const;
		uint32_t setUniform(const std::string& name, const glm::mat3& mat) const;
		uint32_t setUniform(const std::string& name, const glm::mat4& mat) const;
		uint32_t setUniform(const std::string& name, const Ref<Texture2D>& value) const;
	};
}

