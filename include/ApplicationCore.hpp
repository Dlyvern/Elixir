#ifndef APPLICATION_CORE_HPP
#define APPLICATION_CORE_HPP

#pragma once

#include "MainWindow.hpp"

class ApplicationCore
{
private:
    static ApplicationCore* m_Myself;

    ApplicationCore();

    MainWindow m_MainWindow;

    void GameLoop();

public:
    static ApplicationCore* GetReference();

    void Init();

    ~ApplicationCore();
};

#endif //APPLICATION_CORE_HPP
