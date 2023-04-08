#include "BasicTexture.h"
#include <iostream>

#include "stb_image\stb_image.h"

BasicTexture::BasicTexture(const std::string& path)
    : m_RendererID(0), m_FilePath(path), m_Data(nullptr), m_Width(0), m_Height(0), m_Channels(0)
{
    stbi_set_flip_vertically_on_load(1);
    m_Data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Channels, 4);

    GLCall(glGenTextures(1, &m_RendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
    GLCall(glGenerateMipmap(GL_TEXTURE_2D));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Data));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    if (m_Data)
    {
        stbi_image_free(m_Data);
    }
}

BasicTexture::~BasicTexture()
{
    GLCall(glDeleteTextures(1, &m_RendererID));
}

void BasicTexture::Bind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void BasicTexture::Unbind()
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
