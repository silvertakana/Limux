#include "lmxpch.h"

#include "OpenGLVertexArray.h"

namespace LMX
{
	OpenGLVertexArray::OpenGLVertexArray(const LMX::Ref<VertexBuffer>& VBO, const LMX::Ref<IndexBuffer>& EBO, uint32_t offset, uint32_t stride)
		:m_VBO(VBO), m_EBO(EBO)
	{
		LMX_PROFILE_FUNCTION();
		if (ID == 0)glCreateVertexArrays(1, &ID);
		glVertexArrayVertexBuffer(ID, 0, (OpenGLVertexBuffer&)*m_VBO, offset, stride);
		glVertexArrayElementBuffer(ID, (OpenGLIndexBuffer&)*m_EBO);
	}

	void OpenGLVertexArray::Bind() const
	{
		LMX_PROFILE_FUNCTION();
		glBindVertexArray(ID);
	}

	void OpenGLVertexArray::AddAttrib(DataType Type, bool normalized, uint32_t relativeoffset)
	{
		LMX_PROFILE_FUNCTION();
		glEnableVertexArrayAttrib(ID, attribute_count);
		glVertexArrayAttribBinding(ID, attribute_count, 0);
		glVertexArrayAttribFormat(ID, attribute_count++, GetComponentCount(Type), ShaderDataTypeToOpenGLBaseType(Type), normalized ? GL_TRUE : GL_FALSE, relativeoffset);
	}

	void OpenGLVertexArray::UnBind() const
	{
		LMX_PROFILE_FUNCTION();
		glBindVertexArray(0);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		LMX_PROFILE_FUNCTION();
		glDeleteVertexArrays(1, &ID);
	}
}
