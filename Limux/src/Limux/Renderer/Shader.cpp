#include "lmxpch.h"

#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
namespace LMX
{
	Shader* Shader::Create(const std::string& filepath)
	{	
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    LMX_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLShader(filepath);
		}

		LMX_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    LMX_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		LMX_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	
	#define UNIFORM(x, ...) switch (Renderer::GetAPI())\
	{\
		case RendererAPI::API::None:    LMX_ASSERT(false, "RendererAPI::None is currently not supported!"); return 0;\
		case RendererAPI::API::OpenGL:  return ((OpenGLShader*)this)->##x(__VA_ARGS__);\
	}\
	LMX_ASSERT(false, "Unknown RendererAPI!");\
	return 0;
	
	uint32_t Shader::setBool(const std::string& name, bool value) const
	{
		UNIFORM(setBool, name, value);
	}
	uint32_t Shader::setInt(const std::string& name, int value) const
	{
		UNIFORM(setInt, name, value);
	}
	uint32_t Shader::setFloat(const std::string& name, float value) const
	{
		UNIFORM(setFloat, name, value);
	}
	uint32_t Shader::setVec2(const std::string& name, glm::vec2 vec) const
	{
		UNIFORM(setVec2, name, vec);
	}
	uint32_t Shader::setVec3(const std::string& name, glm::vec3 vec) const
	{
		UNIFORM(setVec3, name, vec);
	}
	uint32_t Shader::setVec4(const std::string& name, glm::vec4 vec) const
	{
		UNIFORM(setVec4, name, vec);
	}
	uint32_t Shader::setMat2(const std::string& name, glm::mat2 mat) const
	{
		UNIFORM(setMat2, name, mat);
	}
	uint32_t Shader::setMat3(const std::string& name, glm::mat3 mat) const
	{
		UNIFORM(setMat3, name, mat);
	}
	uint32_t Shader::setMat4(const std::string& name, glm::mat4 mat) const
	{
		UNIFORM(setMat4, name, mat);
	}
}
