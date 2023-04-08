#pragma once

#include "graphics/Renderer.h"

class BasicTexture
{
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char* m_Data;
    int m_Width, m_Height, m_Channels;
    
public:
    BasicTexture(const std::string& path);
    ~BasicTexture();

    void Bind(unsigned int slot = 0) const;
    void Unbind();

    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
};