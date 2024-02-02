#include <string>
#include "MainWindow.hpp"

MainWindow::MainWindow() = default;

void MainWindow::InitWindow(WindowMode windowMode, const std::string &title)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

    m_Monitor = glfwGetPrimaryMonitor();

    if(windowMode == WindowMode::WINDOWED)
    {
        m_CurrentWindowHeight = m_WindowedHeight;
        m_CurrentWindowWidth = m_WindowedWidth;
    }
    else
    {
        m_CurrentWindowHeight = m_FullscreenHeight;
        m_CurrentWindowWidth = m_FullscreenWidth;
    }

    m_WindowMode = windowMode;

    m_Window = glfwCreateWindow(m_CurrentWindowWidth, m_CurrentWindowHeight, title.c_str(), nullptr, nullptr);

    glfwMakeContextCurrent(m_Window);

    glfwSetFramebufferSizeCallback(m_Window, FramebufferSizeCallback);
}

bool MainWindow::WindowIsOpen() const
{
    return !glfwWindowShouldClose(m_Window);
}

void MainWindow::SwapBuffers()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3, 3, 3, 0, 0, 0, 0, 1, 0);
    glBegin(GL_QUADS);
    // Передняя грань
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);

    // Задняя грань
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);

    // Левая грань
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);

    // Правая грань
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, -0.5);

    // Верхняя грань
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);

    // Нижняя грань
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);

    glEnd();
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}

void MainWindow::FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}