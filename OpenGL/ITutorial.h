#pragma once

#include <GLFW\glfw3.h>

#include "helper.h"

#define TUTORIAL_GEN_CLASSNAME(id) Tutorial ## id
#define TUTORIAL_NUM_UNPACKED(num) TUTORIAL_GEN_CLASSNAME(num)
#define TUTORIAL_CLASSNAME TUTORIAL_NUM_UNPACKED(TUTORIAL_NUM)

class ITutorial
{
public:
	virtual Result Init() { return GoodResult(); }
	virtual void Render() = 0;
	virtual void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {}
	virtual ShaderList GetShaderFiles() const { return {}; }
	virtual void SetScreenResolution(int width, int height) {}
	virtual ~ITutorial() = default;
};