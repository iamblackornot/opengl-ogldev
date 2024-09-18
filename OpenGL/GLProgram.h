#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <vector>
#include <unordered_map>

#include "helper.h"

class GLProgram
{
    typedef std::unordered_map<std::string, GLint> VariableMap;
public:

    GLProgram() = default;

    Result Init();
    Result AddShader(ShaderList shaders);
    Result AddShader(ShaderInfo shaderInfo);
    Result CompileShaders();
    GLint GetUniformLocation(std::string_view varName) const;
    GLuint GetHandle();
    bool IsInitialized();
    
    ~GLProgram() noexcept;

private:

    void DeleteShaderObjects();

    GLuint _handle = 0;
	std::vector<GLuint> _shaderObjToDelete;
};
