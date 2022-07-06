#pragma once
#include <glad/glad.h>
#include "Limux/Renderer/VertexArray.h"
#include "OpenGLBuffer.h"
namespace LMX
{
	static GLenum ShaderDataTypeToOpenGLBaseType(DataType type)
	{
		switch (type)
		{
		case LMX::DataType::Float:    return GL_FLOAT;
		case LMX::DataType::Float2:   return GL_FLOAT;
		case LMX::DataType::Float3:   return GL_FLOAT;
		case LMX::DataType::Float4:   return GL_FLOAT;
		case LMX::DataType::Mat3:     return GL_FLOAT;
		case LMX::DataType::Mat4:     return GL_FLOAT;
		case LMX::DataType::Int:      return GL_INT;
		case LMX::DataType::Int2:     return GL_INT;
		case LMX::DataType::Int3:     return GL_INT;
		case LMX::DataType::Int4:     return GL_INT;
		case LMX::DataType::Bool:     return GL_BOOL;
		}

		LMX_ASSERT(false, "Unknown DataType!");
		return 0;
	}
	class OpenGLVertexArray : public VertexArray
	{
	protected:
		LMX::Ref<VertexBuffer> m_VBO;
		LMX::Ref<IndexBuffer> m_EBO;
		uint32_t attribute_count = 0;
		GLuint m_RendererID = 0;
	public:
		OpenGLVertexArray(const LMX::Ref<VertexBuffer>& VBO, const LMX::Ref<IndexBuffer>& EBO, uint32_t offset, uint32_t stride);
		virtual void Bind() const override;
		virtual void UnBind() const override;
		
		virtual const LMX::Ref<VertexBuffer>& GetVBO() const override { return m_VBO; };
		virtual const LMX::Ref<IndexBuffer>&  GetEBO() const override { return m_EBO; };
		virtual uint32_t GetRendererID() const override { return m_RendererID; }
		
		virtual void AddAttrib(DataType Type, bool normalized, uint32_t relativeoffset) override;
		operator GLuint() { return m_RendererID; }
		virtual ~OpenGLVertexArray() override;
	};
}