#pragma once
#include "Buffer.h"
#include "Limux/Core/Core.h"

namespace LMX
{
	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};
	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return 4;
		case ShaderDataType::Float2:   return 4 * 2;
		case ShaderDataType::Float3:   return 4 * 3;
		case ShaderDataType::Float4:   return 4 * 4;
		case ShaderDataType::Mat3:     return 4 * 3 * 3;
		case ShaderDataType::Mat4:     return 4 * 4 * 4;
		case ShaderDataType::Int:      return 4;
		case ShaderDataType::Int2:     return 4 * 2;
		case ShaderDataType::Int3:     return 4 * 3;
		case ShaderDataType::Int4:     return 4 * 4;
		case ShaderDataType::Bool:     return 1;
		}

		LMX_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
	static uint32_t GetComponentCount(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:   return 1;
		case ShaderDataType::Float2:  return 2;
		case ShaderDataType::Float3:  return 3;
		case ShaderDataType::Float4:  return 4;
		case ShaderDataType::Mat3:    return 3 * 3;
		case ShaderDataType::Mat4:    return 4 * 4;
		case ShaderDataType::Int:     return 1;
		case ShaderDataType::Int2:    return 2;
		case ShaderDataType::Int3:    return 3;
		case ShaderDataType::Int4:    return 4;
		case ShaderDataType::Bool:    return 1;
		}

		LMX_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
	
	class VertexArray
	{
	public:
		VertexArray() = default;
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual const LMX::Ref<VertexBuffer>& GetVBO() const = 0;
		virtual const LMX::Ref<IndexBuffer>& GetEBO()  const = 0;
		virtual void AddAttrib(ShaderDataType Type, bool normalized, uint32_t relativeoffset) = 0;
		static Ref<VertexArray> Create(const LMX::Ref<VertexBuffer>& VBO, const LMX::Ref<IndexBuffer>& EBO, uint32_t offset, uint32_t stride);
	};
}