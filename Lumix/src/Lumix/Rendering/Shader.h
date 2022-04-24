#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
namespace LMX
{
	class Shader
	{
	public:
		GLuint ID;
		Shader(GLuint newID) :ID(newID) {}
		Shader(const char* ShaderPath, const std::string& vertexAddon = "", const std::string& fragmentAddon = "");
		Shader(const char* vertexPath, const char* fragmentPath, const std::string& vertexAddon = "", const std::string& fragmentAddon = "");
		void Use() const;
		std::map<std::string, GLuint> TextureUnits, UniformIDs;
		size_t textureCount = 0;
		GLuint ActivateTexture(const std::string& name);
		GLuint GetTextureUnit(const std::string& name);
		GLuint Bindtexture(GLuint textureID, const std::string& textureName);
		GLint GetUni(std::string name) const;

		GLuint setBool(const std::string& name, bool value) const;
		GLuint setInt(const std::string& name, int value) const;
		GLuint setFloat(const std::string& name, float value) const;
		GLuint setVec2(const std::string& name, glm::vec2 vec) const;
		GLuint setVec3(const std::string& name, glm::vec3 vec) const;
		GLuint setVec4(const std::string& name, glm::vec4 vec) const;

		GLuint setBool(GLuint loc, bool value) const;
		GLuint setInt(GLuint loc, int value) const;
		GLuint setFloat(GLuint loc, float value) const;
		GLuint setVec2(GLuint loc, glm::vec2 vec) const;
		GLuint setVec3(GLuint loc, glm::vec3 vec) const;
		GLuint setVec4(GLuint loc, glm::vec4 vec) const;

		static void ShaderErrorCheck(GLuint shader, GLenum pname, const char* shaderPath = "", bool logInfo = false, GLint* code = nullptr, char* log = nullptr);
		operator GLuint() { return ID; }
	};
}