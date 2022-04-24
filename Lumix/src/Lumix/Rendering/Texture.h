#pragma once
#include <glad/glad.h>
namespace LMX
{
	class Texture
	{
	public:
		enum class Types
		{
			diffuse,
			specular,
			normal,
			height
		};
		GLuint ID;
		Types type;
		Texture() = default;
		Texture(const Texture& texture);
		Texture(const std::string& filePath, Types type, bool flip = false, GLenum filt = GL_LINEAR, GLenum wrap = GL_REPEAT);
		void Param(GLenum pname, GLenum param);
		void Bind(GLuint texUnit) const;
		static void UnBind(GLuint texUnit);
		operator GLuint() { return ID; }
	};
}