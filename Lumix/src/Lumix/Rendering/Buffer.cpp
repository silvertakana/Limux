#include "pch.h"

#include "Buffer.h"



//Buffer::Buffer(GLsizeiptr size, void* data, GLenum usage)
//{
//	glCreateBuffers(1, &ID);
//	glNamedBufferData(ID, size, data, usage);
//}
void Buffer::Bind(GLenum target) const
{
	glBindBuffer(target, ID);
}

void Buffer::unBind(GLenum target)
{
	glBindBuffer(target, 0);
}

void Buffer::Delete()
{
	glDeleteBuffers(1, &ID);
}