#pragma once
#include <GL/glew.h>
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <filesystem>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <iostream>

struct ShaderInfo;
typedef std::vector<ShaderInfo> ShaderList;

struct ShaderInfo
{
	GLenum Type;
	std::string FilePath;
};

struct Result
{
	bool IsSuccess;
	std::string Error;

	Result(bool isSuccess, std::string error = {})
		: IsSuccess(isSuccess), Error(error) {}
};

struct GoodResult : public Result
{
	GoodResult() : Result(true) {}
};

struct BadResult : public Result
{
	BadResult(std::string error) : Result(false, error) {}
};

inline std::string GetFileString(std::string filePath)
{
	if (!std::filesystem::exists(filePath)) return {};

	std::fstream input(filePath);
	return std::string(
		std::istreambuf_iterator<char>(input),
		std::istreambuf_iterator<char>());
}

inline std::ostream& operator<<(std::ostream& out, glm::vec4 vec)
{
	return out << std::format("( {}, {}, {}, {} )\n", vec.x, vec.y, vec.z, vec.w);
}

inline std::ostream& operator<<(std::ostream& out, glm::vec3 vec)
{
	return out << std::format("( {}, {}, {} )\n", vec.x, vec.y, vec.z);
}
