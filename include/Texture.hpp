#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>

class Texture
{
private:
    GLuint m_Id;
    int m_Width;
    int m_Height;
    int m_NumChannels;
    unsigned char* m_Data;

public:
    Texture();

    void Load(const std::string& path);

    void Bake();

    void Bind();

    [[nodiscard]]GLuint GetID() const;
};

#endif //TEXTURE_HPP
