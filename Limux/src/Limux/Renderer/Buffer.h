#pragma once
#include "Limux/Core/Core.h"
namespace LMX
{
	class Buffer
	{
	protected:
		uint32_t Size = 0;
	public:
		virtual ~Buffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		
		
		virtual constexpr uint32_t GetSize() const { return Size; };
	};

	class VertexBuffer : public Buffer
	{
	public:
		virtual void SetData(const void* data, uint32_t size) = 0;
		static Ref<VertexBuffer> Create(uint32_t size);
		static Ref<VertexBuffer> Create(void* data, uint32_t size);
	};
	
	class IndexBuffer : public Buffer
	{
	public:
		static Ref<IndexBuffer> Create(void* data, uint32_t size);
	};
}

