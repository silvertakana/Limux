#pragma once
#include <glad/glad.h>
#include "Limux/Renderer/VertexArray.h"
#include "OpenGLBuffer.h"
namespace LMX
{
	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case LMX::ShaderDataType::Float:    return GL_FLOAT;
		case LMX::ShaderDataType::Float2:   return GL_FLOAT;
		case LMX::ShaderDataType::Float3:   return GL_FLOAT;
		case LMX::ShaderDataType::Float4:   return GL_FLOAT;
		case LMX::ShaderDataType::Mat3:     return GL_FLOAT;
		case LMX::ShaderDataType::Mat4:     return GL_FLOAT;
		case LMX::ShaderDataType::Int:      return GL_INT;
		case LMX::ShaderDataType::Int2:     return GL_INT;
		case LMX::ShaderDataType::Int3:     return GL_INT;
		case LMX::ShaderDataType::Int4:     return GL_INT;
		case LMX::ShaderDataType::Bool:     return GL_BOOL;
		}

		LMX_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
	class OpenGLVertexArray : public VertexArray
	{
		LMX::Ref<VertexBuffer> m_VBO;
		LMX::Ref<IndexBuffer> m_EBO;
		uint32_t attribute_count = 0;
	public:
		GLuint ID = 0;
		OpenGLVertexArray(const LMX::Ref<VertexBuffer>& VBO, const LMX::Ref<IndexBuffer>& EBO, uint32_t offset, uint32_t stride);
		virtual void Bind() const override;
		virtual void UnBind() const override;
		
		virtual const LMX::Ref<VertexBuffer>& GetVBO() const override { return m_VBO; };
		virtual const LMX::Ref<IndexBuffer>&  GetEBO() const override { return m_EBO; };
		
		virtual void AddAttrib(ShaderDataType Type, bool normalized, uint32_t relativeoffset) override;
		operator GLuint() { return ID; }
		virtual ~OpenGLVertexArray() override;
	};
}