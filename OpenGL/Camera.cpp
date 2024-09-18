#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 tilt)
	: _position(position), _direction(direction), _tilt(tilt), _strafe(1, 0, 0)
{
	CalculateTilt();
	CalculateStrafe();
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

void Camera::OnKeyEvent(int key, int scancode, int action, int mods)
{
	switch (key)
	{
	case GLFW_KEY_W:
		_position += _cameraSpeed * _direction;
		break;
	case GLFW_KEY_S:
		_position -= _cameraSpeed * _direction;
		break;
	case GLFW_KEY_A:
		_position -= _cameraSpeed * _strafe;
		break;
	case GLFW_KEY_D:
		_position += _cameraSpeed * _strafe;
		break;
	case GLFW_KEY_R:
		_position += _cameraSpeed * _tilt;
		break;
	case GLFW_KEY_F:
		_position -= _cameraSpeed * _tilt;
		break;
	case GLFW_KEY_MINUS:
		_cameraSpeed -= CAMERA_CHANGE_SPEED_STEP;
		_cameraSpeed = std::max(_cameraSpeed, CAMERA_MIN_SPEED);
		break;
	case GLFW_KEY_EQUAL:
		_cameraSpeed += CAMERA_CHANGE_SPEED_STEP;
		break;
	}
}

void Camera::CalculateTilt()
{
	_tilt = glm::cross(_direction, _strafe);
}

void Camera::CalculateStrafe()
{
	_strafe = - glm::cross(_direction, _tilt);
}


