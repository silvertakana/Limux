#include "lmxpch.h"

#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Limux/Core/Core.h"
#include "Limux/Renderer/RendererAPI.h"
namespace LMX
{
	Ref<Shader> Shader::Create(const std::string& fileSrc)
	{	
		LMX_PROFILE_FUNCTION();
		LMX_SWITCHRENDERERAPI(
			return CreateRef<OpenGLShader>(fileSrc);
		);
		return nullptr;
	}
	Ref<Shader> Shader::Create(const std::string& vertexPath, const std::string& fragmentPath)
	{
		LMX_PROFILE_FUNCTION();
		LMX_SWITCHRENDERERAPI(
			return CreateRef<OpenGLShader>(vertexPath, fragmentPath);
		);
		return nullptr;
	}
	Ref<Shader> Shader::Load(const std::string& filePath)
	{
		LMX_PROFILE_FUNCTION();
		LMX_SWITCHRENDERERAPI(
			return OpenGLShader::Load(filePath);
		);
		return nullptr;
	}
	Ref<Shader> Shader::Load(const std::string& vertexPath, const std::string& fragmentPath)
	{
		LMX_PROFILE_FUNCTION();
		LMX_SWITCHRENDERERAPI(
			return OpenGLShader::Load(vertexPath, fragmentPath);
		);
		return nullptr;
	}
	UniformSetter Shader::operator[](const std::string& identifier)
	{
		LMX_PROFILE_FUNCTION();
		return UniformSetter(*this, identifier);
	}
	#define LMX_UNIFORMSETTERFUNCTION(type) \
	void UniformSetter::operator=(type data)\
	{\
		LMX_PROFILE_FUNCTION();\
		LMX_SWITCHRENDERERAPI(\
			((OpenGLShader&)m_Shader).setUniform(m_Identifier, data);\
		);\
	}

	LMX_UNIFORMSETTERFUNCTION(const bool	 &	)
	LMX_UNIFORMSETTERFUNCTION(const int		 &	)
	LMX_UNIFORMSETTERFUNCTION(const float	 &	)
	LMX_UNIFORMSETTERFUNCTION(const glm::vec2&	)
	LMX_UNIFORMSETTERFUNCTION(const glm::vec3&	)
	LMX_UNIFORMSETTERFUNCTION(const glm::vec4&	)
	LMX_UNIFORMSETTERFUNCTION(const glm::mat2&	)
	LMX_UNIFORMSETTERFUNCTION(const glm::mat3&	)
	LMX_UNIFORMSETTERFUNCTION(const glm::mat4&	)
	
}
