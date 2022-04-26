#pragma once
#include <glad/glad.h>
#include "Vertex.h"
namespace LMX
{
	class Buffer
	{
	public:
		GLuint ID = 0;
		Buffer() = default;
		template<class T>
		Buffer(std::vector<T> arr, GLenum usage)
		{
			glCreateBuffers(1, &ID);
			glNamedBufferData(ID, arr.size() * sizeof(T), arr.data(), usage);
		}
		void Bind(GLenum target) const;
		static void unBind(GLenum target);
		void Delete();
		operator GLuint() { return ID; }
		~Buffer()
		{
			//Delete();
		}
	};
}