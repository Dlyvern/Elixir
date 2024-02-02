#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

enum WindowMode
{
    FULLSCREEN,
    WINDOWED
};

class MainWindow
{
private:
    GLFWmonitor* m_Monitor{nullptr};

    GLFWwindow* m_Window{nullptr};

    WindowMode m_WindowMode{WindowMode::WINDOWED};

    int m_WindowedHeight{800};
    int m_WindowedWidth{600};
    int m_FullscreenHeight{1920};
    int m_FullscreenWidth{1080};

    int m_CurrentWindowWidth{0};
    int m_CurrentWindowHeight{0};

    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

public:
    MainWindow();

    void InitWindow(WindowMode windowMode, const std::string& title);


    void SwapBuffers();

    [[nodiscard]] bool WindowIsOpen() const;
};

#endif //MAIN_WINDOW_HPP
