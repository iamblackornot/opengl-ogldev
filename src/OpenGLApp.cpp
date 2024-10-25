#include "OpenGLApp.h"
#include <utility/helper.h>
#include <landfill/landfill.h>

#include <functional>
#include <glm/gtc/type_ptr.hpp>

int OpenGLApp::Run(int argc, char** argv)
{
    Landfill lf;
    lf.TestYawlCalc();
    lf.TestPitchCalc();

    if (!Init()) { return EXIT_FAILURE; }

    GLint gTransformMatrix = _shaders.GetUniformLocation(TRANSFORM_LOCATION);
    if (gTransformMatrix == GL_ERROR)
    {
        std::cout << "failed to get gTransform uniform location" << std::endl;
        return EXIT_FAILURE;
    }

    _camera
        .SetPosition({ 0.0f, 0.0f, 0.0f })
        .SetDirection({ 0.0f, 0.0f, 1.0f })
        .SetTilt({ 0.0f, 1.0f, 0.0f });

    PerspectiveProjectionParams perpectiveParams
    {
        .fov = 45.f,
        .zNear = 1.f,
        .zFar = 10.f,
    };

    Pipeline _pipeline;
    _pipeline
        .Translate({ 0.0f, 0.0f, 2.f })
        .SetPerspective(perpectiveParams);

    Cube cube;

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

    while (!glfwWindowShouldClose(_window.handle))
    {
        glClearColor(0, 0, 0, .7f);
        glClear(GL_COLOR_BUFFER_BIT);

        static float koeff = 0.0f;
        koeff += 0.01f;

        auto transform = _pipeline
            .RotateRadians({ 0.0f, koeff, 0.0f })
            .GetWVPTransform(_camera);

        glUniformMatrix4fv(gTransformMatrix, 1, GL_TRUE, glm::value_ptr(transform));

        glBindBuffer(GL_ARRAY_BUFFER, cube.GetVertexBuffer());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube.GetElementBuffer());

        // position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLVertex), 0);

        // color
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLVertex), (void*)(sizeof(glm::vec3)));

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glDisableVertexAttribArray(0);

        glfwSwapBuffers(_window.handle);
        glfwPollEvents();
    }

    return EXIT_SUCCESS;
}

bool OpenGLApp::Init()
{
    if (!glfwInit())
    {
        std::cout << "failed to init GLFW" << std::endl;
        return false;
    }

    int major;
    int minor;
    int rev;

    glfwGetVersion(&major, &minor, &rev);
    std::cout << std::format("GLFW {}.{}.{} initialized", major, minor, rev) << std::endl;

    _window = CreateSmallWindow();

    if(!_window.handle) {
        const char* error = NULL;
        int error_code = glfwGetError(&error);

        std::cout << std::format("failed to create window: [{}] - {}", error_code, error);
        return false;
    }

    glfwMakeContextCurrent(_window.handle);

    GLenum glewRes = glewInit();
    if (glewRes != GLEW_OK)
    {
        std::cout << glewGetErrorString(glewRes) << std::endl;
        return false;
    }

    Result shadersRes = InitShaders();
    if (!shadersRes.IsSuccess)
    {
        std::cout << std::format("failed to init shaders, reason {}", shadersRes.Error) << std::endl;
    }


    //glfwSetWindowPos(window, 100, 100);
    SetGLFWCallbacks();

    return true;
}

Result OpenGLApp::InitShaders()
{
    Result res = _shaders.Init();
    if (!res.IsSuccess) return res;

    res = _shaders.AddShader(GetShaderFiles());
    if (!res.IsSuccess) return res;

    res = _shaders.CompileShaders();
    if (!res.IsSuccess) return res;

    return res;
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

void OpenGLApp::SetGLFWCallbacks()
{
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(GLDebugMessageCallback, nullptr);
    //glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_HIGH, 0, nullptr, GL_TRUE);

    auto errorCallback = [this](int error, const char* description)
    {
        std::cout << std::format("Error {}: {}\n", error, description);
    };

    GLFWCWrapper::GLFWSetErrorCallback(errorCallback);

    auto keyCallback = [this](GLFWwindow* window, int key, int scancode, int action, int mods) -> void
    {
        OnKeyEvent(key, scancode, action, mods);
    };

    GLFWCWrapper::GLFWSetKeyCallback(_window.handle, keyCallback);

    auto cameraRotateCallback = [this](double xDelta, double yDelta) -> void
    {
        OnCameraRotate(xDelta, yDelta);
    };

    _mouseTracker = std::make_unique<MouseTracker>(_window.handle, cameraRotateCallback);
}

void OpenGLApp::OnKeyEvent(int key, int scancode, int action, int mod)
{
    switch (key)
    {
    case GLFW_KEY_W:
        _camera.MoveForward();
        break;
    case GLFW_KEY_S:
        _camera.MoveBackward();
        break;
    case GLFW_KEY_A:
        _camera.MoveLeft();
        break;
    case GLFW_KEY_D:
        _camera.MoveRight();
        break;
    case GLFW_KEY_R:
        _camera.MoveUp();
        break;
    case GLFW_KEY_F:
        _camera.MoveDown();
        break;
    case GLFW_KEY_MINUS:
        _camera.DecreaseSpeed();
        break;
    case GLFW_KEY_EQUAL:
        _camera.IncreaseSpeed();
        break;
    }
}

void OpenGLApp::OnCameraRotate(double xDelta, double yDelta)
{
    std::cout << "Mouse moved while RMB pressed: deltaX = " << xDelta << ", deltaY = " << yDelta << std::endl;
    float sensitivity = 1.f;
    _camera.Rotate(xDelta * sensitivity, yDelta * sensitivity);
}

OpenGLApp::~OpenGLApp() noexcept
{
    if (_window.handle) { glfwDestroyWindow(_window.handle); }

    glfwTerminate();
}

Window::Window() : handle(nullptr), width(0), height(0)
{
}

Window::Window(GLFWwindow* handle, int width, int height)
    : handle(handle), width(width), height(height)
{
}

ShaderList OpenGLApp::GetShaderFiles() const
{
    return ShaderList
    {
        { GL_VERTEX_SHADER,   "shaders\\tut14\\shader.vs" },
        { GL_FRAGMENT_SHADER, "shaders\\tut14\\shader.fs" },
    };
}