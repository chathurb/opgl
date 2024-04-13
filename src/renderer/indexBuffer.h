#pragma once

class indexBuffer
{
private:
    unsigned int m_rendererID;

public:
    unsigned int m_count;
    
    indexBuffer(const unsigned int* data, unsigned int count);
    ~indexBuffer();

    void Bind() const;
    void Unbind() const;
};