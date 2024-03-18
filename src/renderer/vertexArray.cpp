#include "vertexArray.h"

vertexArray::vertexArray()
{
    GLCall(glGenVertexArrays(1, &m_rendererID));
}

vertexArray::~vertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_rendererID));
}

void vertexArray::AddBuffer(const vertexBuffer& vb, const vertexBufferLayout& layout, const indexBuffer& ib)
{
    Bind();
    vb.Bind();

    const auto& elements = layout.m_Elements;
    unsigned int offset = 0;

    for(unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type,
            element.normalized, layout.m_Stride, (const void*)offset));
        offset += element.count * vertexBufferElement::GetSizeOfType(element.type);
    }

    ib.Bind();
}

void vertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_rendererID));
}

void vertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
}