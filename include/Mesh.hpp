#ifndef ELIXIR_MESH_HPP
#define ELIXIR_MESH_HPP

#include "Common.hpp"
#include <vector>
#include <GL/glew.h>

class Mesh
{
private:
    std::vector<Vertex> m_Vertices;
    std::vector<GLuint> m_Indices;
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices);

    void Bind();

    void Draw();

};

#endif //ELIXIR_MESH_HPP
