#include "lmxpch.h"
#include "OpenGLShader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "Limux/Core/AssetLoader.h"

namespace LMX
{
	void CreateOGLShader(const std::string& vertexSrc, const std::string& fragmentSrc, uint32_t& ID)
	{
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
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		CreateOGLShader(vertexSrc, fragmentSrc, ID);
	}
	OpenGLShader::OpenGLShader(const std::string& shaderSrc)
	{
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
	OpenGLShader* OpenGLShader::Load(const std::string& shaderPath)
	{
		return new OpenGLShader(AssetLoader::LoadFile(shaderPath));
	}
	OpenGLShader* OpenGLShader::Load(const std::string& vertexPath, const std::string& fragmentPath)
	{
		return new OpenGLShader(AssetLoader::LoadFile(vertexPath), AssetLoader::LoadFile(fragmentPath));
	}
	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(ID);
	}
	void OpenGLShader::Bind() const
	{
		glUseProgram(ID);
	}
	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}
	uint32_t OpenGLShader::GetUni(const std::string & name) const
	{
		return glGetUniformLocation(ID, name.c_str());
	}
	uint32_t OpenGLShader::setBool(const std::string& name, bool value) const
	{
		return setBool(GetUni(name.c_str()), value);
	}
	uint32_t OpenGLShader::setInt(const std::string& name, int value) const
	{
		return setInt(GetUni(name.c_str()), value);
	}
	uint32_t OpenGLShader::setFloat(const std::string& name, float value) const
	{
		return setFloat(GetUni(name.c_str()), value);
	}
	uint32_t OpenGLShader::setVec2(const std::string& name, glm::vec2 vec) const
	{
		return setVec2(GetUni(name.c_str()), vec);
	}
	uint32_t OpenGLShader::setVec3(const std::string& name, glm::vec3 vec) const
	{
		return setVec3(GetUni(name.c_str()), vec);
	}
	uint32_t OpenGLShader::setVec4(const std::string& name, glm::vec4 vec) const
	{
		return setVec4(GetUni(name.c_str()), vec);
	}

	uint32_t OpenGLShader::setMat2(const std::string& name, glm::mat2 mat) const
	{
		return setMat2(GetUni(name.c_str()), mat);
	}

	uint32_t OpenGLShader::setMat3(const std::string& name, glm::mat3 mat) const
	{
		return setMat3(GetUni(name.c_str()), mat);
	}

	uint32_t OpenGLShader::setMat4(const std::string& name, glm::mat4 mat) const
	{
		return setMat4(GetUni(name.c_str()), mat);
	}

	uint32_t OpenGLShader::setBool(uint32_t loc, bool value) const
	{
		Bind();
		glUniform1i(loc, (int)value);
		return loc;
	}
	uint32_t OpenGLShader::setInt(uint32_t loc, int value) const
	{
		Bind();
		glUniform1i(loc, value);
		return loc;
	}
	uint32_t OpenGLShader::setFloat(uint32_t loc, float value) const
	{
		Bind();
		glUniform1f(loc, value);
		return loc;
	}
	uint32_t OpenGLShader::setVec2(uint32_t loc, glm::vec2 vec) const
	{
		Bind();
		glUniform2f(loc, vec.x, vec.y);
		return loc;
	}
	uint32_t OpenGLShader::setVec3(uint32_t loc, glm::vec3 vec) const
	{
		Bind();
		glUniform3f(loc, vec.x, vec.y, vec.z);
		return loc;
	}
	uint32_t OpenGLShader::setVec4(uint32_t loc, glm::vec4 vec) const
	{
		Bind();
		glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
		return loc;
	}
	uint32_t OpenGLShader::setMat2(uint32_t loc, glm::mat2 mat) const
	{
		Bind();
		glUniformMatrix2fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
		return loc;
	}
	uint32_t OpenGLShader::setMat3(uint32_t loc, glm::mat3 mat) const
	{
		Bind();
		glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
		return loc;
	}
	uint32_t OpenGLShader::setMat4(uint32_t loc, glm::mat4 mat) const
	{
		Bind();
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
		return loc;
	}
}