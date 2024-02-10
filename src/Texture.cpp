#define STB_IMAGE_IMPLEMENTATION

#include "stb/stb_image.h"

#include "Texture.hpp"

Texture::Texture() = default;

void Texture::Load(const std::string &path)
{
    std::string full_path = "../resources/textures/" + path;
    stbi_set_flip_vertically_on_load(false);

    m_Data = stbi_load(full_path.data() , &m_Width, &m_Height, &m_NumChannels, 0);
}

void Texture::Bake()
{
    if(!m_Data) return;

    glGenTextures(1, &m_Id);
    glBindTexture(GL_TEXTURE_2D, m_Id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLint format;

    if(m_NumChannels == 3)
        format = GL_RGB;
    else if(m_NumChannels == 4)
        format = GL_RGBA;
    else if(m_NumChannels == 1)
        format = GL_RED;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_Data);

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(m_Data);

    m_Data = nullptr;
}

GLuint Texture::GetID() const
{
    return m_Id;
}

void Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_Id);
}

