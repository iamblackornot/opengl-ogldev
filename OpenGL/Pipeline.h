#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <numbers>

#include "Camera.h"

struct WorldTransformParams
{
	glm::vec3 position = { 0, 0, 0 };
	glm::vec3 scale = { 1, 1, 1 };
	glm::vec3 rotation = { 0, 0, 0 };
};

struct PerspectiveProjectionParams
{
	int width = 640;
	int height = 480;
	float fov = 80;
	float zNear = 1;
	float zFar = 100;
};

class Pipeline
{
public:
	Pipeline() = default;
	Pipeline& Translate(glm::vec3 const& position);
	Pipeline& Scale(glm::vec3 const& scaleFactor);
	Pipeline& RotateDegrees(glm::vec3 const& rotation);
	Pipeline& RotateRadians(glm::vec3 const& rotation);
	Pipeline& SetPerspective(PerspectiveProjectionParams const& params);
	Pipeline& SetCamera(Camera const& camera);
	Pipeline& SetResolution(int width, int height);
	glm::mat4 GetWorldTransform() const;
	glm::mat4 GetPerspectiveTransform() const;
	glm::mat4 GetViewTransform() const;
	glm::mat4 GetWPTransform() const;
	glm::mat4 GetWVPTransform() const;

	void OnKeyEvent(int key, int scancode, int action, int mods);
private:
	float ToRadians(float degrees) const;
	float ToDegrees(float radians) const;

	glm::mat4 GetTranslateTransform(float x, float y, float z) const;
	glm::mat4 GetScaleTransform(float xScale, float yScale, float zScale) const;
	glm::mat4 GetXRotateTransform(float xRadians) const;
	glm::mat4 GetYRotateTransform(float radians) const;
	glm::mat4 GetZRotateTransform(float radians) const;
	glm::mat4 GetChangeBasisTransform() const;

private:
	WorldTransformParams _world;
	PerspectiveProjectionParams _perspective;
	Camera _camera;
};