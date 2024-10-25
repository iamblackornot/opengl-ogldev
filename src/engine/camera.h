#pragma once

#include "utility/helper.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>

namespace camera_utility
{
	inline constexpr float MAX_YAWL  =  180.0f;
	inline constexpr float MIN_YAWL  = -180.0f;

	inline constexpr float MAX_PITCH =   90.0f;
	inline constexpr float MIN_PITCH =  -90.0f;

	float CalculateYawl(glm::vec3 direction);
	float CalculatePitch(glm::vec3 direction);
}

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

	void IncreaseSpeed();
	void DecreaseSpeed();

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();
	void MoveForward();
	void MoveBackward();
	void Rotate(float yawDelta, float pitchDelta);
private:
	void CalculateTilt();
	void CalculateStrafe();
public:
	constexpr static float CAMERA_MIN_SPEED = 0.01f;
	constexpr static float CAMERA_CHANGE_SPEED_STEP = 0.01f;
private:
	float _cameraSpeed = 0.1f;

	float _yawl = 0.f;
	float _pitch = 0.f;

	glm::vec3 _position   { 0, 0, 0 };
	glm::vec3 _direction  { 0, 0, 1 };
	glm::vec3 _tilt       { 0, 1, 0 };
	glm::vec3 _strafe	  { 1, 0, 0 };
};