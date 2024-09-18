#pragma once

#include "helper.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <iostream>

class Camera
{
public:
	Camera() = default;
	Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 tilt);

	glm::vec3 GetPosition() const;
	glm::vec3 GetDirection() const;
	glm::vec3 GetTilt() const;
	glm::vec3 GetStrafe() const;

	Camera& SetPosition(glm::vec3 pos);
	Camera& SetDirection(glm::vec3 direction);
	Camera& SetTilt(glm::vec3 tilt);

	void OnKeyEvent(int key, int scancode, int action, int mods);

private:
	void CalculateTilt();
	void CalculateStrafe();
public:
	constexpr static float CAMERA_MIN_SPEED = 0.01f;
	constexpr static float CAMERA_CHANGE_SPEED_STEP = 0.01f;
private:
	float _cameraSpeed = 0.1f;

	glm::vec3 _position   { 0, 0, 0 };
	glm::vec3 _direction  { 0, 0, 1 };
	glm::vec3 _tilt       { 0, 1, 0 };
	glm::vec3 _strafe	  { 1, 0, 0 };
};