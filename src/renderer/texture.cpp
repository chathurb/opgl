#include "texture.h"

#include "stb_image.h"

texture::texture(const std::string& path)
    : m_rendererID(0), m_filePath(path), m_localBuffer(nullptr),
    m_width(0), m_height(0), m_bpp(0)
{
    stbi_set_flip_vertically_on_load(1);
    m_localBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4);

    GLCall(glGenTextures(1, &m_rendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    if(m_localBuffer)
        stbi_image_free(m_localBuffer);
}

texture::~texture()
{
    GLCall(glDeleteTextures(1, &m_rendererID));
}

void texture::Bind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_rendererID));
}

void texture::Unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));   
}