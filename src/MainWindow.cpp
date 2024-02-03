#include <string>
#include "MainWindow.hpp"

MainWindow::MainWindow() = default;

void MainWindow::InitWindow(WindowMode windowMode, const std::string &title)
{
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

    glfwSwapBuffers(m_Window);
    glfwPollEvents();
}

void MainWindow::FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}