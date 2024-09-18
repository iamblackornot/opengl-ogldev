#include "Pipeline.h"

Pipeline& Pipeline::Translate(glm::vec3 const& position)
{
	_world.position = position;
	return *this;
}

Pipeline& Pipeline::Scale(glm::vec3 const& scaleFactor)
{
	_world.scale = scaleFactor;
	return *this;
}

Pipeline& Pipeline::RotateDegrees(glm::vec3 const& rotation)
{
	_world.rotation = glm::vec3
	(
		ToRadians(rotation.x),
		ToRadians(rotation.y),
		ToRadians(rotation.z)
	);
	return *this;
}

Pipeline& Pipeline::RotateRadians(glm::vec3 const& rotation)
{
	_world.rotation = rotation;
	return *this;
}

Pipeline& Pipeline::SetPerspective(PerspectiveProjectionParams const& params)
{
	_perspective = params;
	return *this;
}

Pipeline& Pipeline::SetCamera(Camera const& camera)
{
	_camera = camera;
	return *this;
}

Pipeline& Pipeline::SetResolution(int width, int height)
{
	_perspective.width = width;
	_perspective.height = height;
	return *this;
}

float Pipeline::ToRadians(float degrees) const
{
	return static_cast<float>(degrees * std::numbers::pi / 180.0f);
}

float Pipeline::ToDegrees(float radians) const
{
	return static_cast<float>(radians * 180.0f / std::numbers::pi);
}

glm::mat4 Pipeline::GetTranslateTransform(float x, float y, float z) const
{
	return glm::mat4
	(
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1
	);
}

glm::mat4 Pipeline::GetScaleTransform(float xScale, float yScale, float zScale) const
{
	float x = xScale;
	float y = yScale;
	float z = zScale;

	return glm::mat4
	(
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1
	);
}

glm::mat4 Pipeline::GetXRotateTransform(float radians) const
{
	float x11 =  cos(radians);
	float x12 = -sin(radians);
	float x21 =  sin(radians);
	float x22 =  cos(radians);

	return glm::mat4
	(
		1,   0,	  0,   0,
		0, x11, x12,   0,
		0, x21, x22,   0,
		0,   0,	  0,   1
	);
}

glm::mat4 Pipeline::GetYRotateTransform(float radians) const
{
	float y00 =  cos(radians);
	float y02 =  sin(radians);
	float y20 = -sin(radians);
	float y22 =  cos(radians);

	return glm::mat4
	(
		y00,   0, y02,	 0,
		  0,   1,	0,	 0,
		y20,   0, y22,	 0,
		  0,   0,   0,	 1
	);
}

glm::mat4 Pipeline::GetZRotateTransform(float radians) const
{
	float z00 =  cos(radians);
	float z01 = -sin(radians);
	float z10 =  sin(radians);
	float z11 =  cos(radians);

	return glm::mat4
	(
		z00, z10,	0,	 0,
		z01, z11,	0,	 0,
		  0,   0,	1,	 0,
		  0,   0,	0,	 1
	);
}

glm::mat4 Pipeline::GetPerspectiveTransform() const
{
	float aspect_ratio =
		static_cast<float>(_perspective.height) / static_cast<float>(_perspective.width);
	//printf("height = %d, width = %d", _perspective.height, _perspective.width);
	float tanHalfFOV = tan(ToRadians(_perspective.fov / 2.f));
	float projPaneDist = 1.f / tanHalfFOV;

	float x00 = aspect_ratio * projPaneDist;
	float y11 = projPaneDist;
	float zNear = _perspective.zNear;
	float zFar = _perspective.zFar;
	float zRange = zFar - zNear;
	float z22 = (zFar + zNear) / zRange;
	float z23 = -2.f * zFar * zNear / zRange;

	return glm::mat4
	(
		x00,   0,   0,   0,
		  0, y11,   0,   0,
		  0,   0, z22, z23,
		  0,   0,   1,   0
	);
}

glm::mat4 Pipeline::GetViewTransform() const
{
	glm::mat4 translate = GetTranslateTransform(
								- _camera.GetPosition().x,
								- _camera.GetPosition().y,
								- _camera.GetPosition().z);

	glm::mat4 changeBasis = GetChangeBasisTransform();

	return translate * changeBasis;
}

glm::mat4 Pipeline::GetWorldTransform() const
{
	glm::mat4 scale = GetScaleTransform(
								_world.scale.x,
								_world.scale.y,
								_world.scale.z);
	glm::mat4 xRotation = GetXRotateTransform(_world.rotation.x);
	glm::mat4 yRotation = GetYRotateTransform(_world.rotation.y);
	glm::mat4 zRotation = GetZRotateTransform(_world.rotation.z);
	glm::mat4 translation = GetTranslateTransform(
								_world.position.x,
								_world.position.y,
								_world.position.z);

	return scale * xRotation * yRotation * zRotation * translation;
}

glm::mat4 Pipeline::GetChangeBasisTransform() const
{
	glm::vec3 N = _camera.GetDirection();
	glm::vec3 V = _camera.GetTilt();
	glm::vec3 U = _camera.GetStrafe();

	return glm::mat4
	(
		U.x,  U.y,  U.z,   0,
		V.x,  V.y,  V.z,   0,
		N.x,  N.y,  N.z,   0,
		  0,    0,    0,   1
	);
}

glm::mat4 Pipeline::GetWPTransform() const
{
	return GetWorldTransform() * GetPerspectiveTransform();
}

glm::mat4 Pipeline::GetWVPTransform() const
{
	return GetWorldTransform() * GetViewTransform() * GetPerspectiveTransform();
}

void Pipeline::OnKeyEvent(int key, int scancode, int action, int mods)
{
	_camera.OnKeyEvent(key, scancode, action, mods);
}