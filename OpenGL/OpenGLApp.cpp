#include "OpenGLApp.h"
#include "helper.h"

#include <functional>

int OpenGLApp::Run(int argc, char** argv)
{
    if (!glfwInit())
    {
        std::cout << "failed to init GLFW" << std::endl;
        return EXIT_FAILURE;
    }

    auto errorCallback = [this](int error, const char* description)
    {
        OnError(error, description);
    };
    
    GLWFCWrapper::GLFWSetErrorCallback(errorCallback);

    //GLFWwindow* window = CreateSmallTestWindow();
    Window const window = CreateSmallWindow();
    //Window const window = CreateBorderlessFullScreenWindow();

    if (!window.handle)
    {
        std::cout << "failed to create GLFWwindow" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    //glfwSetWindowPos(window, 100, 100);

    glfwMakeContextCurrent(window.handle);

    GLenum res = glewInit();
    if (res != GLEW_OK)
    {
        std::cout << glewGetErrorString(res) << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    _tutorial = std::make_unique<TUTORIAL_CLASSNAME>();

    Result tutInitRes = _tutorial->Init();
    _tutorial->SetScreenResolution(window.width, window.height);

    if (!tutInitRes.IsSuccess)
    {
        std::cout << tutInitRes.Error;
        return EXIT_FAILURE;
    }

    auto keyCallback = [this](GLFWwindow* window, int key, int scancode, int action, int mods) -> void
    {
        _tutorial->OnKeyEvent(window, key, scancode, action, mods);
    };

    GLWFCWrapper::GLFWSetKeyCallback(window.handle, keyCallback);

    while (!glfwWindowShouldClose(window.handle))
    {
        glClearColor(0, 0, 0, .7f);
        glClear(GL_COLOR_BUFFER_BIT);

        _tutorial->Render();

        glfwSwapBuffers(window.handle);
        glfwPollEvents();
    }

    return EXIT_SUCCESS;
}

Window OpenGLApp::CreateBorderlessFullScreenWindow() const
{
    auto monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    return Window(
        glfwCreateWindow(mode->width, mode->height, "OPEN GL Tutorial", monitor, NULL),
        mode->width,
        mode->height);
}

Window OpenGLApp::CreateSmallWindow() const
{
    return Window(
        glfwCreateWindow(SMALL_SCREEN_WIDTH, SMALL_SCREEN_HEIGHT, "OPEN GL Tutorial", NULL, NULL),
        SMALL_SCREEN_WIDTH,
        SMALL_SCREEN_HEIGHT);
}

void OpenGLApp::OnError(int error, const char* description)
{
    std::cout << std::format("Error {}: {}\n", error, description);
}

OpenGLApp::~OpenGLApp() noexcept
{
    glfwTerminate();
}

Window::Window(GLFWwindow* handle, int width, int height)
    : handle(handle), width(width), height(height)
{
}

Window::~Window()
{
    if(handle) 
    {
        glfwDestroyWindow(handle);
    }
}
