#include "lmxpch.h"
#include "OpenGLShader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "Limux/Core/AssetLoader.h"

namespace LMX
{
	void CreateOGLShader(const std::string& vertexSrc, const std::string& fragmentSrc, uint32_t& ID)
	{
		LMX_PROFILE_FUNCTION();
		uint32_t vertexShader, fragmentShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		{
			std::string version = "#version 460 core\n";
			std::string vertex = version + vertexSrc;
			std::string fragment = version + fragmentSrc;


			const GLchar* vertexCode = vertex.c_str();
			const GLchar* fragmentCode = fragment.c_str();
			glShaderSource(vertexShader, 1, &vertexCode, NULL);
			glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
			glCompileShader(vertexShader);
			glCompileShader(fragmentShader);
		}


		ID = glCreateProgram();

		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);
		glDetachShader(ID, vertexShader);
		glDetachShader(ID, vertexShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		LMX_PROFILE_FUNCTION();
		CreateOGLShader(vertexSrc, fragmentSrc, ID);
	}
	OpenGLShader::OpenGLShader(const std::string& shaderSrc)
	{
		LMX_PROFILE_FUNCTION();
		std::stringstream file;
		file << shaderSrc;
		std::string line, source[2];
		enum Mode
		{
			NONE = -1,
			VERTEX, FRAGMENT
		};
		Mode mode = NONE;
		const char* typeToken = "#type";
		while (std::getline(file, line))
		{
			if (line.contains("#shader"))
			{
				if (line.contains("vertex"))
					mode = VERTEX;
				else if (line.contains("fragment"))
					mode = FRAGMENT;
				else
					mode = NONE;
			}
			else if (mode != NONE)
				source[mode] += line + '\n';
		}
		CreateOGLShader(source[VERTEX], source[FRAGMENT], ID);
	}
	Ref<OpenGLShader> OpenGLShader::Load(const std::string& shaderPath)
	{
		LMX_PROFILE_FUNCTION();
		return CreateRef<OpenGLShader>(AssetLoader::LoadFile(shaderPath));
	}
	Ref<OpenGLShader> OpenGLShader::Load(const std::string& vertexPath, const std::string& fragmentPath)
	{
		LMX_PROFILE_FUNCTION();
		return CreateRef<OpenGLShader>(AssetLoader::LoadFile(vertexPath), AssetLoader::LoadFile(fragmentPath));
	}
	OpenGLShader::~OpenGLShader()
	{
		LMX_PROFILE_FUNCTION();
		glDeleteProgram(ID);
	}
	void OpenGLShader::Bind() const
	{
		LMX_PROFILE_FUNCTION();
		glUseProgram(ID);
	}
	void OpenGLShader::Unbind() const
	{
		LMX_PROFILE_FUNCTION();
		glUseProgram(0);
	}
	uint32_t OpenGLShader::GetUni(const std::string & name) const
	{
		LMX_PROFILE_FUNCTION();
		return glGetUniformLocation(ID, name.c_str());
	}
	uint32_t OpenGLShader::setUniform(const std::string& name, bool value) const
	{
		LMX_PROFILE_FUNCTION();
		uint32_t location = GetUni(name);
		glUniform1i(location, (int)value);
		return location;
	}
	uint32_t OpenGLShader::setUniform(const std::string& name, int value) const
	{
		LMX_PROFILE_FUNCTION();
		uint32_t location = GetUni(name);
		glUniform1i(location, value);
		return location;
	}
	uint32_t OpenGLShader::setUniform(const std::string& name, float value) const
	{
		LMX_PROFILE_FUNCTION();
		uint32_t location = GetUni(name);
		glUniform1f(location, value);
		return location;
	}
	uint32_t OpenGLShader::setUniform(const std::string& name, const glm::vec2& value) const
	{
		LMX_PROFILE_FUNCTION();
		uint32_t location = GetUni(name);
		glUniform2f(location, value.x, value.y);
		return location;
	}
	uint32_t OpenGLShader::setUniform(const std::string& name, const glm::vec3& value) const
	{
		LMX_PROFILE_FUNCTION();
		uint32_t location = GetUni(name);
		glUniform3f(location, value.x, value.y, value.z);
		return location;
	}
	uint32_t OpenGLShader::setUniform(const std::string& name, const glm::vec4& value) const
	{
		LMX_PROFILE_FUNCTION();
		uint32_t location = GetUni(name);
		glUniform4f(location, value.x, value.y, value.z, value.w);
		return location;
	}
	uint32_t OpenGLShader::setUniform(const std::string& name, const glm::mat2& value) const
	{
		LMX_PROFILE_FUNCTION();
		uint32_t location = GetUni(name);
		glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(value));
		return location;
	}
	uint32_t OpenGLShader::setUniform(const std::string& name, const glm::mat3& value) const
	{
		LMX_PROFILE_FUNCTION();
		uint32_t location = GetUni(name);
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
		return location;
	}
	uint32_t OpenGLShader::setUniform(const std::string& name, const glm::mat4& value) const
	{
		LMX_PROFILE_FUNCTION();
		uint32_t location = GetUni(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
		return location;
	}
	uint32_t OpenGLShader::setUniform(const std::string& name, const Ref<Texture2D>& value) const
	{
		LMX_PROFILE_FUNCTION();
		uint32_t location = GetUni(name);
		glUniform1i(location, std::static_pointer_cast<OpenGLTexture2D>(value)->ID);
		return location;
	}
}