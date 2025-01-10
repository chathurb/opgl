#pragma once

class vertexBuffer
{
private:
    unsigned int m_rendererID;

public:
    vertexBuffer(const void* data, unsigned int size);
    ~vertexBuffer();

    void Bind() const;
    void Unbind() const;
    void UpdateBuffer(const void* data, unsigned int size);
};