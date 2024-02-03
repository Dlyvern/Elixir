////#include "ApplicationCore.hpp"
////
////int main()
////{
////    ApplicationCore::GetReference()->Init();
////}

#include "Shader.hpp"
#include "Texture.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

struct Vertex
{
    glm::vec3 position;
    glm::vec2 textureCoordinates;
};


void Rotate(glm::mat4 &matrix, float angle, const glm::vec3& axis)
{
    matrix = glm::rotate(matrix, glm::radians(angle), axis);
}

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Cube", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glewInit();

    glewExperimental = GL_TRUE;
    glViewport(0, 0, 800,600);


    std::vector<Vertex> vertices
    {
        {{-0.5f, -0.5f, -0.5f},  {0.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f},  {1.0f, 0.0f}},
        {{0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f}, { 0.0f, 1.0f}},

        {{-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f}},
        {{0.5f, -0.5f,  0.5f},  {1.0f, 0.0f}},
        {{0.5f,  0.5f,  0.5f},  {1.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f},  {0.0f, 1.0f}},

        {{-0.5f, -0.5f, -0.5f},  {1.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f},  {0.0f, 0.0f}},
        {{0.5f, -0.5f,  0.5f},  {0.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f},  {1.0f, 1.0f}},

        {{-0.5f,  0.5f, -0.5f},  {1.0f, 0.0f}},
        {{0.5f,  0.5f, -0.5f},  {0.0f, 0.0f}},
        {{0.5f,  0.5f,  0.5f},  {0.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f},  {1.0f, 1.0f}},

        {{-0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f}},

        {{0.5f, -0.5f, -0.5f},  {1.0f, 1.0f}},
        {{0.5f,  0.5f, -0.5f},  {0.0f, 1.0f}},
        {{0.5f,  0.5f,  0.5f},  {0.0f, 0.0f}},
        {{0.5f, -0.5f,  0.5f},  {1.0f, 0.0f}}
    };

    std::vector<GLuint>indices
    {
            0, 1, 2,
            2, 3, 0,
            4, 5, 6,
            6, 7, 4,
            8, 9, 10,
            10, 11, 8,
            12, 13, 14,
            14, 15, 12,
            16, 17, 18,
            18, 19, 16,
            20, 21, 22,
            22, 23, 20
    };

    Shader shader;
    shader.Load("cube.vert", "cube.frag");

    GLuint VBO, VAO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, position));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, textureCoordinates));


    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    Texture texture;
    texture.Load("smoking_weed.png");
    texture.Bake();

    glm::mat4 rotationMatrix = glm::mat4(1.0f);

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        GLint rotationMatrixLoc = glGetUniformLocation(shader.GetProgram(), "rotationMatrix");

        Rotate(rotationMatrix, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        glUniformMatrix4fv(rotationMatrixLoc, 1, GL_FALSE, glm::value_ptr(rotationMatrix));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.GetID());
        glUniform1i(glGetUniformLocation(shader.GetProgram(), "texture1"), 0);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    shader.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}