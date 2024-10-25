#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <vector>
#include <unordered_map>

#include "utility/helper.h"

struct ShaderInfo;
typedef std::vector<ShaderInfo> ShaderList;

struct ShaderInfo
{
    GLenum Type;
    std::string FilePath;
};


class GLProgram
{
    typedef std::unordered_map<std::string, GLint> VariableMap;
public:

    GLProgram() = default;

    Result Init();
    Result AddShader(ShaderList shaders);
    Result AddShader(ShaderInfo shaderInfo);
    Result CompileShaders() const;
    GLint GetUniformLocation(std::string_view varName) const;
    GLuint GetHandle() const;
    bool IsInitialized() const;
    
    ~GLProgram() noexcept;

private:

    void DeleteShaderObjects();

    GLuint _handle = 0;
	std::vector<GLuint> _shaderObjToDelete;
};
