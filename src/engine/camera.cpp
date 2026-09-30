#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 tilt) :
	_position(position), 
	_direction(glm::normalize(direction)),
	_tilt(glm::normalize(tilt)),
	_strafe(1, 0, 0)
{
	CalculateStrafe();
	CalculateTilt();
}

glm::vec3 Camera::GetPosition() const
{
	return _position;
}

glm::vec3 Camera::GetDirection() const
{
	return _direction;
}

glm::vec3 Camera::GetTilt() const
{
	return _tilt;
}

glm::vec3 Camera::GetStrafe() const
{
	return _strafe;
}

Camera& Camera::SetPosition(glm::vec3 pos)
{
	_position = pos;
	return *this;
}

Camera& Camera::SetDirection(glm::vec3 direction)
{
	_direction = glm::normalize(direction);
	CalculateTilt();

	return *this;
}

Camera& Camera::SetTilt(glm::vec3 tilt)
{
	_tilt = glm::normalize(tilt);
	CalculateStrafe();

	return *this;
}

void Camera::IncreaseSpeed()
{
	_cameraSpeed += CAMERA_CHANGE_SPEED_STEP;
}

void Camera::DecreaseSpeed()
{
	_cameraSpeed -= CAMERA_CHANGE_SPEED_STEP;
	_cameraSpeed = std::max(_cameraSpeed, CAMERA_MIN_SPEED);
}

void Camera::MoveLeft()
{
	_position -= _cameraSpeed * _strafe;
}

void Camera::MoveRight()
{
	_position += _cameraSpeed * _strafe;
}

void Camera::MoveUp()
{
	_position += _cameraSpeed * _tilt;
}

void Camera::MoveDown()
{
	_position -= _cameraSpeed * _tilt;
}

void Camera::MoveForward()
{
	_position += _cameraSpeed * _direction;
}

void Camera::MoveBackward()
{
	_position -= _cameraSpeed * _direction;
}

void Camera::CalculateTilt()
{
	_tilt = glm::normalize(glm::cross(_direction, _strafe));
}

void Camera::CalculateStrafe()
{
	_strafe = - glm::normalize(glm::cross(_direction, _tilt));
}

void Camera::Rotate(double yawDelta, double pitchDelta)
{
	float yaw = glm::radians(static_cast<float>(yawDelta));

	glm::quat qYaw = glm::angleAxis(yaw, glm::vec3(0, 1, 0));

	_direction = qYaw * _direction;
	_strafe = qYaw * _strafe;
	_tilt = qYaw * _tilt;

	float pitch = glm::radians(static_cast<float>(pitchDelta));

	glm::quat qPitch = glm::angleAxis(pitch, _strafe);

	_direction = qPitch * _direction;
	_tilt = qPitch * _tilt;
}
