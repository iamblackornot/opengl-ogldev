#include "GLProgram.h"

Result GLProgram::Init()
{
    _handle = glCreateProgram();

    if (_handle == 0) return BadResult("failed to init GLProgram");

    return GoodResult();
}

Result GLProgram::AddShader(ShaderList shaders)
{
    for (ShaderInfo const& info : shaders)
    {
        auto const& res = AddShader(info);
        if (!res.IsSuccess) return res;
    }

    return GoodResult();
}

Result GLProgram::AddShader(ShaderInfo shaderInfo)
{
    if (!IsInitialized())
        return BadResult("GLProgram is not initialized");

    std::string shaderSource = GetFileString(shaderInfo.FilePath);

    if (shaderSource.empty())
        return BadResult(std::format("shader source file not found [{}]", shaderInfo.FilePath));

    GLuint hShaderObj = glCreateShader(shaderInfo.Type);

    if (hShaderObj == 0)
        return BadResult(std::format("failed to create shader object [{}]", shaderInfo.FilePath));

    GLchar const* shaderSources[1];
    shaderSources[0] = shaderSource.c_str();

    GLint sourceLengths[1]{};
    sourceLengths[0] = static_cast<GLint>(shaderSource.size());

    glShaderSource(hShaderObj, 1, shaderSources, sourceLengths);
    glCompileShader(hShaderObj);

    GLint compileRes;

    glGetShaderiv(hShaderObj, GL_COMPILE_STATUS, &compileRes);

    if (!compileRes)
    {
        GLchar info[1024];
        glGetShaderInfoLog(hShaderObj, sizeof(info), NULL, info);
        glDeleteShader(hShaderObj);

        return BadResult(std::format("error compiling shader [{}]: \n '{}'", shaderInfo.FilePath, info));
    }

    _shaderObjToDelete.push_back(hShaderObj);
    glAttachShader(_handle, hShaderObj);

    return GoodResult();
}

Result GLProgram::CompileShaders() const
{
    glLinkProgram(_handle);

    GLint res;
    GLchar error[1024] = { 0 };

    glGetProgramiv(_handle, GL_LINK_STATUS, &res);

    if (!res) {
        glGetProgramInfoLog(_handle, sizeof(error), NULL, error);
        return BadResult(std::format("error linking shader program: '{}'", error));
    }

    glValidateProgram(_handle);
    glGetProgramiv(_handle, GL_VALIDATE_STATUS, &res);
    if (!res) {
        glGetProgramInfoLog(_handle, sizeof(error), NULL, error);
        return BadResult(std::format("invalid shader program: '{}'", error));
    }

    glUseProgram(_handle);

    return GoodResult();
}

GLint GLProgram::GetUniformLocation(std::string_view varName) const
{
    return glGetUniformLocation(_handle, varName.data());
}

GLuint GLProgram::GetHandle() const
{
    return _handle;
}

bool GLProgram::IsInitialized() const
{
    return _handle > 0;
}

GLProgram::~GLProgram() noexcept
{
    DeleteShaderObjects();

    if (IsInitialized())
    {
        glDeleteProgram(_handle);
        glUseProgram(0);
    }
}

void GLProgram::DeleteShaderObjects()
{
    for (GLuint hShader : _shaderObjToDelete)
    {
        if (IsInitialized())
            glDetachShader(_handle, hShader);

        glDeleteShader(hShader);
    }

    _shaderObjToDelete.clear();
}
