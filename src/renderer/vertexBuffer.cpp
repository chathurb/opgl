#include "vertexBuffer.h"

#include "utils.h"

vertexBuffer::vertexBuffer(const void* data, unsigned int size)
{
    GLCall(glGenBuffers(1, &m_rendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
}

vertexBuffer::~vertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_rendererID));
}

void vertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
}

void vertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void vertexBuffer::UpdateBuffer(const void* data, unsigned int size)
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID))
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data ))
}