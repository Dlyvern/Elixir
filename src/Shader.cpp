#include "Shader.hpp"


Shader::Shader() = default;


Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
{
    Load(vertexPath, fragmentPath);
}

int Shader::CheckErrors(GLuint shader, bool isProgram)
{
    GLint is_linked;

    char info_log[512];

    if(isProgram)
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &is_linked);

        if (!is_linked)
        {
            glGetProgramInfoLog(shader, 512, nullptr, info_log);
            std::cerr << "Program linking error" << std::endl;
        }
    }
    else
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &is_linked);

        if(!is_linked)
        {
            glGetShaderInfoLog(shader, 512, nullptr, info_log);
            std::cerr << "Shader compilation error" << std::endl;
        }
    }

    return is_linked;
}

void Shader::Load(const std::string &vertexPath, const std::string &fragmentPath)
{
    std::string vertex_source = FileSystem::ReadTextFromFile("../resources/shaders/" + vertexPath);
    std::string fragment_source = FileSystem::ReadTextFromFile("../resources/shaders/" + fragmentPath);

    const char* vertex_code = vertex_source.c_str();
    const char* fragment_code = fragment_source.c_str();

    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertex_code, nullptr);
    glCompileShader(vertex);

    CheckErrors(vertex);

    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragment_code, nullptr);
    glCompileShader(fragment);

    CheckErrors(fragment);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex);
    glAttachShader(shader_program, fragment);
    glLinkProgram(shader_program);

    if(CheckErrors(shader_program, true))
    {
        m_ShaderProgram = shader_program;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::Use()
{
    glUseProgram(m_ShaderProgram);
}

void Shader::Delete()
{
    glDeleteProgram(m_ShaderProgram);
}

GLuint Shader::GetProgram() const
{
    return m_ShaderProgram;
}

