#include "ApplicationCore.hpp"

ApplicationCore* ApplicationCore::m_Myself;

ApplicationCore::ApplicationCore() = default;

ApplicationCore *ApplicationCore::GetReference()
{
    if(!m_Myself)
        m_Myself = new ApplicationCore;

    return m_Myself;
}

void ApplicationCore::Init()
{
    glfwInit();

    glfwSetErrorCallback([](int error, const char* description)
    {
        std::cerr << "Glfw error (" << std::to_string(error) << "). Description: " << description << "\n";
    });

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);


    m_MainWindow.InitWindow(WindowMode::WINDOWED, "Elixir");

    GameLoop();
}

void ApplicationCore::GameLoop()
{
    while(m_MainWindow.WindowIsOpen())
    {
        m_MainWindow.SwapBuffers();
    }
}

ApplicationCore::~ApplicationCore() = default;