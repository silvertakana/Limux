#pragma once
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

		
		static Buffer* Create(void* data, uint32_t size) = delete;
	};

	class VertexBuffer : public Buffer
	{
	public:
		static VertexBuffer* Create(void* data, uint32_t size);
	};
	
	class IndexBuffer : public Buffer
	{
	public:
		static IndexBuffer* Create(void* data, uint32_t size);
	};
}

