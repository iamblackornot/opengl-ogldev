#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>
#include <memory>
#include <iostream>

#include <GL/GLProgram.h>
#include <utility/GLFW_C_Wrapper.h>
#include <utility/GLFW_DebugInfo.h>
#include <utility/helper.h>
#include <utility/mouse_tracker.h>
#include <engine/pipeline.h>
#include <objects/cube.h>

constexpr int SMALL_SCREEN_WIDTH = 800;
constexpr int SMALL_SCREEN_HEIGHT = 600;

constexpr char const TRANSFORM_LOCATION[] = "gTransform";

using MouseTrackerOpt = std::optional<std::reference_wrapper<MouseTracker const>>;
using MouseTrackerRef = std::unique_ptr<MouseTracker>;

struct Window 
{
    Window();
    Window(GLFWwindow* pointer, int width, int height);

    GLFWwindow* handle;
    int width;
    int height;
};

class OpenGLApp
{
public:
    OpenGLApp() = default;
    ~OpenGLApp() noexcept;
    int Run(int argc, char** argv);
private:
    bool Init();
    Result InitShaders();
    Window CreateBorderlessFullScreenWindow() const;
    Window CreateSmallWindow() const;

    void SetGLFWCallbacks();
    void OnKeyEvent(int key, int scancode, int action, int mod);
    void OnCameraRotate(double xDelta, double yDelta);
    ShaderList GetShaderFiles() const;

    Window _window;
    Camera _camera;
    GLProgram _shaders;
    MouseTrackerRef _mouseTracker;
};