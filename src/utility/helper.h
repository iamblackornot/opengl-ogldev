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
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>
#include <random>

constexpr double EPSILON = 1e-6;
constexpr GLint GL_ERROR = -1;

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

inline std::ostream& operator<<(std::ostream& out, glm::quat q)
{
	return out << std::format("( {}, {}, {}, {} )\n", q.w, q.x, q.y, q.z);
}

inline std::ostream& operator<<(std::ostream& out, glm::vec4 vec)
{
	return out << std::format("( {}, {}, {}, {} )\n", vec.x, vec.y, vec.z, vec.w);
}

inline std::ostream& operator<<(std::ostream& out, glm::vec3 vec)
{
	return out << std::format("( {}, {}, {} )\n", vec.x, vec.y, vec.z);
}

inline glm::vec3 GenerateRandomColor()
{
	static std::mt19937 random{ std::random_device()() };
	static std::uniform_int_distribution<std::mt19937::result_type> dist(0, 255);

	return 
	{ 
		(float)dist(random) / (float)255,
		(float)dist(random) / (float)255,
		(float)dist(random) / (float)255
	};
}

inline bool fequal(float lhs, float rhs)
{
	return glm::epsilonEqual(lhs, rhs, glm::epsilon<float>());
}

inline bool fless(float lhs, float rhs)
{
	return glm::epsilonEqual(lhs, rhs, glm::epsilon<float>()) ? false : lhs < rhs;
}