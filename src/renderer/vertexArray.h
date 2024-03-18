#pragma once

#include "vertexBuffer.h"
#include "vertexBufferLayout.h"
#include "indexBuffer.h"

class vertexArray
{
private:
    unsigned int m_rendererID;

public:
    vertexArray();
    ~vertexArray();

    void AddBuffer(const vertexBuffer& vb, const vertexBufferLayout& layout, const indexBuffer& ib);

    void Bind() const;
    void Unbind() const;
};