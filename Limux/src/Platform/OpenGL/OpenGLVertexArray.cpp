#include "lmxpch.h"

#include "OpenGLVertexArray.h"

namespace LMX
{
	OpenGLVertexArray::OpenGLVertexArray(const LMX::Ref<VertexBuffer>& VBO, const LMX::Ref<IndexBuffer>& EBO, uint32_t offset, uint32_t stride)
		:m_VBO(VBO), m_EBO(EBO)
	{
		LMX_PROFILE_FUNCTION();
		if (m_RendererID == 0) glCreateVertexArrays(1, &m_RendererID);
		glVertexArrayVertexBuffer(m_RendererID, 0, (OpenGLVertexBuffer&)*m_VBO, offset, stride);
		glVertexArrayElementBuffer(m_RendererID, (OpenGLIndexBuffer&)*m_EBO);
	}

	void OpenGLVertexArray::Bind() const
	{
		LMX_PROFILE_FUNCTION();
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::AddAttrib(DataType Type, bool normalized, uint32_t relativeoffset)
	{
		LMX_PROFILE_FUNCTION();
		glEnableVertexArrayAttrib(m_RendererID, attribute_count);
		glVertexArrayAttribBinding(m_RendererID, attribute_count, 0);
		glVertexArrayAttribFormat(m_RendererID, attribute_count++, GetComponentCount(Type), ShaderDataTypeToOpenGLBaseType(Type), normalized ? GL_TRUE : GL_FALSE, relativeoffset);
	}

	void OpenGLVertexArray::UnBind() const
	{
		LMX_PROFILE_FUNCTION();
		glBindVertexArray(0);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		LMX_PROFILE_FUNCTION();
		glDeleteVertexArrays(1, &m_RendererID);
	}
}
