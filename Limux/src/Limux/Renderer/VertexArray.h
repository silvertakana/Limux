#pragma once
#include "Buffer.h"
#include "Limux/Core/Base.h"
#include "RendererDataType.h"

namespace LMX
{
	class VertexArray
	{
	public:
		VertexArray() = default;
		virtual ~VertexArray() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		virtual const LMX::Ref<VertexBuffer>& GetVBO() const = 0;
		virtual const LMX::Ref<IndexBuffer>& GetEBO()  const = 0;
		virtual uint32_t GetRendererID() const = 0;

		virtual void AddAttrib(DataType Type, bool normalized, uint32_t relativeoffset) = 0;
		static Ref<VertexArray> Create(const LMX::Ref<VertexBuffer>& VBO, const LMX::Ref<IndexBuffer>& EBO, uint32_t offset, uint32_t stride);
	};
}