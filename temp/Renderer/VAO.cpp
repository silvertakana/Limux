#include "lmxpch.h"

#include "VAO.h"

namespace LMX
{
	VertArrObj::VertArrObj()
	{
		glCreateVertexArrays(1, &ID);
	}

	void VertArrObj::Link(GLuint VBO, GLuint EBO, GLintptr offset, GLsizei stride, GLuint bindingindex)
	{
		glVertexArrayVertexBuffer(ID, bindingindex, VBO, offset, stride);
		glVertexArrayElementBuffer(ID, EBO);
	}

	void VertArrObj::Bind() const
	{
		glBindVertexArray(ID);
	}

	void VertArrObj::Attrib(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset, GLuint bindingindex)
	{
		glEnableVertexArrayAttrib(ID, attribindex);
		glVertexArrayAttribBinding(ID, attribindex, bindingindex);
		glVertexArrayAttribFormat(ID, attribindex, size, type, normalized, relativeoffset);
	}

	void VertArrObj::unBind()
	{
		glBindVertexArray(0);
	}

	void VertArrObj::Delete()
	{
		glDeleteVertexArrays(1, &ID);
	}
}
