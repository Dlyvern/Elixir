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
#include "Common.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"

void Rotate(glm::mat4 &matrix, float angle, const glm::vec3& axis)
{
    matrix = glm::rotate(matrix, glm::radians(angle), axis);
}

const int width = 800;
const int height = 600;

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL Cube", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glewInit();

    glewExperimental = GL_TRUE;
    glViewport(0, 0, 800,600);

    glEnable(GL_DEPTH_TEST);

//Pyramid
//    std::vector<Vertex> vertices =
//    {
//            {{-0.5f, 0.0f, 0.5f}, {0.0f, 0.0f}},
//            {{-0.5f, 0.0f, -0.5f}, {5.0f, 0.0f}},
//            {{0.5f, 0.0f, -0.5f}, {0.0f, 0.0f}},
//            {{0.5f, 0.0f, 0.5f}, {5.0f, 0.0f}},
//            {{0.0f, 0.8f, 0.0f}, {2.5f, 5.0f}},
//    };
//
//    std::vector<GLuint> indices =
//    {
//            0, 1, 2,
//            0, 2, 3,
//            0, 1, 4,
//            1, 2, 4,
//            2, 3, 4,
//            3, 0, 4
//    };


//Cube
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

//Plane
//    std::vector<Vertex>vertices =
//    {
//            {{-1.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
//            {{-1.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
//            {{1.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
//            {{1.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
//    };
//
//    std::vector<GLuint>indices =
//    {
//        0, 1, 2,
//        0, 2, 3
//    };


    Shader shader;
    shader.Load("cube.vert", "cube.frag");

    Mesh mesh(vertices, indices);
    mesh.Bind();

    Texture texture;
    texture.Load("smoking_weed.png");
    texture.Bake();
    glUniform1i(glGetUniformLocation(shader.GetProgram(), "texture1"), 0);



//    float rotation = 0.0f;
//    double prev_time = glfwGetTime();

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        camera.Inputs(window);

        camera.Matrix(45.0f, 0.1f, 100.0f, shader, "camMatrix");

//        double current_time = glfwGetTime();
//
//        if(current_time - prev_time >= 1 / 60)
//        {
//            rotation += 0.5;
//            prev_time = current_time;
//        }
//
//        glm::mat4 model = glm::mat4(1.0f);
//        glm::mat4 view = glm::mat4(1.0f);
//        glm::mat4 projection = glm::mat4(1.0f);
//
//        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
//        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
//        projection = glm::perspective(glm::radians(45.0f), float(width / height), 0.1f, 100.0f);
//
//        int model_loc = glGetUniformLocation(shader.GetProgram(), "model");
//        glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));
//
//        int view_loc = glGetUniformLocation(shader.GetProgram(), "view");
//        glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(view));
//
//        int projection_loc = glGetUniformLocation(shader.GetProgram(), "projection");
//        glUniformMatrix4fv(projection_loc, 1, GL_FALSE, glm::value_ptr(projection));



        texture.Bind();

        mesh.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    shader.Delete();


    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}