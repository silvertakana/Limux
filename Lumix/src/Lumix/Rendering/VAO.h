#pragma once
#include <glad/glad.h>
namespace LMX
{
	class VertArrObj
	{
	public:
		GLuint ID;
		VertArrObj();
		void Link(GLuint VBO, GLuint EBO, GLintptr offset, GLsizei stride, GLuint bindingindex = 0);
		void Bind() const;
		void Attrib(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset, GLuint bindingindex = 0);
		static void unBind();
		void Delete();
		operator GLuint() { return ID; }
		~VertArrObj()
		{
			//Delete();
		}
	};


}