#pragma once

#include <GLFW\glfw3.h>
#include <functional>

using KeyCallback				= std::function<void(GLFWwindow* window, int key, int scancode, int action, int mods)>;
using ErrorCallback				= std::function<void(int error, const char* description)>;
using CursorPositionCallback	= std::function<void(GLFWwindow* window, double xpos, double ypos)>;
using MouseButtonCallback		= std::function<void(GLFWwindow* window, int button, int action, int mods)>;

class GLFWCWrapper
{
public:
	static void GLFWSetKeyCallback(GLFWwindow* window, KeyCallback&& callable)
	{
		keyCallback = std::move(callable);
		glfwSetKeyCallback(window, &glfwKeyCallbackInternal);
	}
	static void GLFWSetErrorCallback(ErrorCallback&& callable)
	{
		errorCallback = std::move(callable);
		glfwSetErrorCallback(&glfwErrorCallbackInternal);
	}
	static void GLFWSetCursorPositionCallback(GLFWwindow* window, CursorPositionCallback&& callable)
	{
		cursorPositionCallback = std::move(callable);
		glfwSetCursorPosCallback(window, &glfwCursorPositionCallbackInternal);
	}
	static void GLFWSetMouseButtonCallback(GLFWwindow* window, MouseButtonCallback&& callable)
	{
		mouseButtonCallback = std::move(callable);
		glfwSetMouseButtonCallback(window, &glfwMouseButtonCallbackInternal);
	}
private:
	static void glfwKeyCallbackInternal(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		keyCallback(window, key, scancode, action, mods);
	}
	static void glfwErrorCallbackInternal(int error, const char* description)
	{
		errorCallback(error, description);
	}
	static void glfwCursorPositionCallbackInternal(GLFWwindow* window, double xpos, double ypos)
	{
		cursorPositionCallback(window, xpos, ypos);
	}
	static void glfwMouseButtonCallbackInternal(GLFWwindow* window, int button, int action, int mods)
	{
		mouseButtonCallback(window, button, action, mods);
	}
private:
	static KeyCallback				keyCallback;
	static ErrorCallback			errorCallback;
	static CursorPositionCallback	cursorPositionCallback;
	static MouseButtonCallback		mouseButtonCallback;
};

inline KeyCallback				GLFWCWrapper::keyCallback				= [] (GLFWwindow* window, int key, int scancode, int action, int mods) {};
inline ErrorCallback			GLFWCWrapper::errorCallback				= [] (int error, const char* description) {};
inline CursorPositionCallback	GLFWCWrapper::cursorPositionCallback	= [] (GLFWwindow* window, double xpos, double ypos) {};
inline MouseButtonCallback		GLFWCWrapper::mouseButtonCallback		= [] (GLFWwindow* window, int button, int action, int mods) {};