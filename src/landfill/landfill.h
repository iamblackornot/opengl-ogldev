#include <utility/helper.h>
#include <engine/camera.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

struct Landfill
{
	void PrintYawlAngles();
	void PrintPitchAngles();
	void TestYawlCalc();
	void TestPitchCalc();

	void AssertFloatEqual(float expected, float actual, std::string caption, float precision = glm::epsilon<float>());

};