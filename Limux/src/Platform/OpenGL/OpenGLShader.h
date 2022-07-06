#pragma once
#include <glm/glm.hpp>
#include <Limux/Core/Base.h>
#include "Limux/Renderer/Shader.h"
#include "OpenGLTexture.h"
namespace LMX
{
	class OpenGLShader : public Shader
	{
	protected:
		uint32_t m_RendererID;
	public:
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

		virtual uint32_t GetRendererID() const override { return m_RendererID; }
		uint32_t GetUni(const std::string& name) const;

		uint32_t setUniform(const std::string& name, const bool     & data, bool senderror) const;
		uint32_t setUniform(const std::string& name, const int      & data, bool senderror) const;
		uint32_t setUniform(const std::string& name, const float    & data, bool senderror) const;
		uint32_t setUniform(const std::string& name, const glm::vec2& data, bool senderror) const;
		uint32_t setUniform(const std::string& name, const glm::vec3& data, bool senderror) const;
		uint32_t setUniform(const std::string& name, const glm::vec4& data, bool senderror) const;
		uint32_t setUniform(const std::string& name, const glm::mat2& data, bool senderror) const;
		uint32_t setUniform(const std::string& name, const glm::mat3& data, bool senderror) const;
		uint32_t setUniform(const std::string& name, const glm::mat4& data, bool senderror) const;
	};
}

