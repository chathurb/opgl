#pragma once

#include "utils.h"

#include <string>

class texture
{
private:
    unsigned int m_rendererID;
    std::string m_filePath;
    unsigned char* m_localBuffer;
    int m_width, m_height, m_bpp;

public:
    texture(const std::string& path);
    ~texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;
};