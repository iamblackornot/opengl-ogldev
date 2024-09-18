#pragma once

#include <GLFW\glfw3.h>
#include <functional>

//GLFWkeyfun
using SetKeyCallback = std::function<void(GLFWwindow* window, int key, int scancode, int action, int mods)>;
using SetErrorCallback = std::function<void(int error, const char* description)>;

class GLWFCWrapper
{
public:
	static void GLFWSetKeyCallback(GLFWwindow* window, SetKeyCallback&& callable)
	{
		setKeyCallback = std::forward<SetKeyCallback>(callable);
		glfwSetKeyCallback(window, &glfwSetKeyCallbackInternal);
	}
	static void GLFWSetErrorCallback(SetErrorCallback&& callable)
	{
		setErrorCallback = std::forward<SetErrorCallback>(callable);
		glfwSetErrorCallback(&glfwSetErrorCallbackInternal);
	}
private:
	static void glfwSetKeyCallbackInternal(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		setKeyCallback(window, key, scancode, action, mods);
	}
	static void glfwSetErrorCallbackInternal(int error, const char* description)
	{
		setErrorCallback(error, description);
	}
private:
	static SetKeyCallback setKeyCallback;
	static SetErrorCallback setErrorCallback;
};

inline SetKeyCallback GLWFCWrapper::setKeyCallback = [] (GLFWwindow* window, int key, int scancode, int action, int mods) {};
inline SetErrorCallback GLWFCWrapper::setErrorCallback = [] (int error, const char* description) {};