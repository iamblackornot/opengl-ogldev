#include "camera.h"

namespace camera_utility
{
	float CalculateYawl(glm::vec3 direction)
	{
		direction = glm::normalize(direction);

		float degrees = glm::degrees(glm::acos(direction.z));
		degrees *= fless(direction.x, 0) ? -1 : 1;

		return degrees;
	}

	float CalculatePitch(glm::vec3 direction)
	{
		direction = glm::normalize(direction);

		float degrees = glm::degrees(glm::acos(direction.y));
		degrees *= fless(direction.z, 0) ? 1 : -1;

		return degrees;
	}
}

Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 tilt) :
	_yawl(camera_utility::CalculateYawl(direction)),
	_pitch(camera_utility::CalculatePitch(direction)),
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
	_tilt = glm::cross(_direction, _strafe);
}

void Camera::CalculateStrafe()
{
	_strafe = - glm::cross(_direction, _tilt);
}

void Camera::Rotate(float yawDelta, float pitchDelta)
{
	_yawl += yawDelta;
	_yawl = _yawl > camera_utility::MAX_YAWL ? _yawl - 360.f : _yawl;
	_yawl = _yawl < camera_utility::MIN_YAWL ? _yawl + 360.f : _yawl;

	_pitch += pitchDelta;
	_pitch = std::min(_pitch, camera_utility::MAX_PITCH);
	_pitch = std::max(_pitch, camera_utility::MIN_PITCH);

	glm::vec3 eulerRadians(glm::radians(_pitch), glm::radians(_yawl), 0.f);
	glm::quat qrotation(eulerRadians);

	static glm::vec3 zAxis{ 0, 0, 1 };
	static glm::vec3 xAxis{ 1, 0, 0 };

	_direction = zAxis * qrotation;
	_strafe    = xAxis * qrotation;

	_tilt = glm::cross(_direction, _strafe);
	std::cout << _tilt;
}
