#pragma once

#define TUT14 1

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <stdlib.h>
#include <memory>
#include <iostream>

#include "GLFW_C_Wrapper.h"
#include "tutorials.h"

constexpr int SMALL_SCREEN_WIDTH = 800;
constexpr int SMALL_SCREEN_HEIGHT = 600;

struct Window 
{
    Window(GLFWwindow* pointer, int width, int height);
    ~Window();

    GLFWwindow* handle;
    int width;
    int height;
};

class OpenGLApp
{
    typedef std::unique_ptr<ITutorial> TutorialPtr;
public:
    OpenGLApp() = default;
    ~OpenGLApp() noexcept;
    int Run(int argc, char** argv);
private:
    Window CreateBorderlessFullScreenWindow() const;
    Window CreateSmallWindow() const;

    void OnError(int error, const char* description);

    TutorialPtr _tutorial;
};