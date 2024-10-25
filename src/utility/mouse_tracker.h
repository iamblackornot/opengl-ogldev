#include <functional>

#include <GLFW/glfw3.h>
#include <utility/GLFW_C_Wrapper.h>

using CameraRotateCallback = std::function<void(double, double)>;

class MouseTracker
{
public:
	MouseTracker(GLFWwindow* window, CameraRotateCallback&& cb) :
		_rmbPressed(false),
		_lastX(0),
		_lastY(0),
		_totalDeltaX(0),
		_totalDeltaY(0),
		_onCameraRotate(std::move(cb))
	{
		auto mouseButtonCallback = [&](GLFWwindow* window, int button, int action, int mods) 
		{
			if (button == GLFW_MOUSE_BUTTON_RIGHT)
			{
				if (action == GLFW_PRESS) {
					_rmbPressed = true;
					glfwGetCursorPos(window, &_lastX, &_lastY);
				}
				else if (action == GLFW_RELEASE) {
					_rmbPressed = false;
				}
			}
		};
		
		auto cursorPositionCallback = [&, this](GLFWwindow* window, double xpos, double ypos) 
		{
			if (_rmbPressed) 
			{
				double deltaX = xpos - _lastX;
				double deltaY = ypos - _lastY;

				if (_onCameraRotate) { _onCameraRotate(deltaX, deltaY); }

				_lastX = xpos;
				_lastY = ypos;
			}
		};

		GLFWCWrapper::GLFWSetMouseButtonCallback(window, mouseButtonCallback);
		GLFWCWrapper::GLFWSetCursorPositionCallback(window, cursorPositionCallback);
	};

	MouseTracker(MouseTracker const&) = delete;
	MouseTracker(MouseTracker&&) = delete;

private:
	bool	_rmbPressed;
	double	_lastX;
	double	_lastY;
	double	_totalDeltaX;
	double	_totalDeltaY;

	CameraRotateCallback _onCameraRotate;
};