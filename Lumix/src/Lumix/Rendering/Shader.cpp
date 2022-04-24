#include "pch.h"

#include "Shader.h"
#include "LoadFiles.h"
#include "Log.h"
void Create(const char* vertexBody, const char* fragmentBody, const char* vertexPath, const char* fragmentPath, GLuint& ID, const char* vertexAddon = "", const char* fragmentAddon = "")
{
	GLuint vertexShader, fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	{
		auto S_vertexCode = std::string("#version 460\n")+ vertexAddon+"\n"+ vertexBody;
		auto S_fragmentCode = std::string("#version 460\n")+ fragmentAddon+"\n"+ fragmentBody;
		const char* vertexCode = S_vertexCode.c_str();
		const char* fragmentCode = S_fragmentCode.c_str();
		glShaderSource(vertexShader, 1, &vertexCode, NULL);
		glShaderSource(fragmentShader, 1, &fragmentCode, NULL);
		glCompileShader(vertexShader);
		//Shader::ShaderErrorCheck(vertexShader, GL_COMPILE_STATUS, vertexPath, true);
		glCompileShader(fragmentShader);
		//Shader::ShaderErrorCheck(fragmentShader, GL_COMPILE_STATUS, fragmentPath, true);
	}

	ID = glCreateProgram();

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	std::string joinedPath = vertexPath;
	joinedPath = joinedPath + " | " + fragmentPath;
	//Shader::ShaderErrorCheck(ID, GL_LINK_STATUS, joinedPath.c_str(), true);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
Shader::Shader(const char* ShaderPath, const std::string& vertexAddon, const std::string& fragmentAddon)
{
	auto [vertex, fragment] = loadShader(ShaderPath);
	Create(vertex.c_str(), fragment.c_str(), ShaderPath, ShaderPath, ID, vertexAddon.c_str(), fragmentAddon.c_str());
}

Shader::Shader(const char* vertexPath, const char* fragmentPath, const std::string& vertexAddon, const std::string& fragmentAddon)
{
	auto vertex = loadFile(vertexPath);
	auto fragment = loadFile(fragmentPath);
	Create(vertex.c_str(), fragment.c_str(), vertexPath, fragmentPath, ID, vertexAddon.c_str(), fragmentAddon.c_str());
}

void Shader::Use() const
{
	glUseProgram(ID);
}

GLuint Shader::ActivateTexture(const std::string& name)
{
	setInt(name, TextureUnits[name]=textureCount++);
	return textureCount;
}

GLuint Shader::GetTextureUnit(const std::string& name)
{
	return TextureUnits[name];
}

GLuint Shader::Bindtexture(GLuint textureID, const std::string& textureName)
{
	if (!TextureUnits.contains(textureName))
		ActivateTexture(textureName);
	glBindTextureUnit(TextureUnits[textureName], textureID);
	return TextureUnits[textureName];
}

void Shader::ShaderErrorCheck(GLuint shader, GLenum pname, const char* shaderPath, bool logInfo, GLint* code, char* log)
{
	int  success;
	char infoLog[512];
	glGetShaderiv(shader, pname, &success);
	if(code)*code = success;
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		ASSERT(logInfo, "ShaderError: {1}\n{0}", infoLog, shaderPath);
		if (log)strcpy_s(infoLog, log);
	}
}
static std::map<GLuint, std::map<std::string, GLuint>> UniformDictionary;
GLint Shader::GetUni(std::string name) const
{
	GLint UniLoc;
	if (UniformDictionary.contains(this->ID) and UniformDictionary[this->ID].contains(name))
	{
		UniLoc = UniformDictionary[this->ID][name];
	}
	else
	{
		UniLoc = glGetUniformLocation(ID, name.c_str());
		UniformDictionary[this->ID][name] = UniLoc;
	}
	if (UniLoc == -1)
		ERROR("Unable to locate uniform named: {0}", name);
	return UniLoc;
}
GLuint Shader::setBool(const std::string& name, bool value) const
{
	return setBool(GetUni(name.c_str()), value);
}
GLuint Shader::setInt(const std::string& name, int value) const
{
	return setInt(GetUni(name.c_str()), value);
}
GLuint Shader::setFloat(const std::string& name, float value) const
{
	return setFloat(GetUni(name.c_str()), value);
}
GLuint Shader::setVec2(const std::string& name, glm::vec2 vec) const
{
	return setVec2(GetUni(name.c_str()), vec);
}
GLuint Shader::setVec3(const std::string& name, glm::vec3 vec) const
{
	return setVec3(GetUni(name.c_str()), vec);
}
GLuint Shader::setVec4(const std::string& name, glm::vec4 vec) const
{
	return setVec4(GetUni(name.c_str()), vec);
}

GLuint Shader::setBool(GLuint loc, bool value) const
{
	Use();
	glUniform1i(loc, (int)value);
	return loc;
}
GLuint Shader::setInt(GLuint loc, int value) const
{
	Use();
	glUniform1i(loc, value);
	return loc;
}
GLuint Shader::setFloat(GLuint loc, float value) const
{
	Use();
	glUniform1f(loc, value);
	return loc;
}
GLuint Shader::setVec2(GLuint loc, glm::vec2 vec) const
{
	Use();
	glUniform2f(loc, vec.x, vec.y);
	return loc;
}
GLuint Shader::setVec3(GLuint loc, glm::vec3 vec) const
{
	Use();
	glUniform3f(loc, vec.x, vec.y, vec.z);
	return loc;
}
GLuint Shader::setVec4(GLuint loc, glm::vec4 vec) const
{
	Use();
	glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
	return loc;
}
