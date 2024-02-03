#ifndef SHADER_HPP
#define SHADER_HPP

#include "FileSystem.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader
{
private:
    GLuint m_ShaderProgram;

    static int CheckErrors(GLuint shader, bool isProgram = false);
public:
    Shader();

    Shader(const std::string&vertexPath, const std::string& fragmentPath);

    void Load(const std::string&vertexPath, const std::string& fragmentPath);

    void Use();

    void Delete();

    [[nodiscard]]GLuint GetProgram() const;
};

#endif //SHADER_HPP
