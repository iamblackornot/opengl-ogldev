#include "landfill.h"

void Landfill::PrintYawlAngles()
{
	{
		float angle = 45.f;
		glm::vec3 zAxis{ 0, 0, 1 };
		glm::quat qyaw = glm::angleAxis(glm::radians(angle), glm::vec3(0, 1, 0));

		glm::vec3 direction = qyaw * zAxis;

		std::cout << "initial angle = " << angle << std::endl;
		std::cout << "direction = " << direction;
		std::cout << "arccos = " << glm::acos(direction.z) << std::endl;
		std::cout << "arccos (degrees) = " << glm::degrees(glm::acos(direction.z)) << std::endl;
	}

	std::cout << std::endl;

	{
		float angle = 0.f;
		glm::vec3 zAxis{ 0, 0, 1 };
		glm::quat qyaw = glm::angleAxis(glm::radians(angle), glm::vec3(0, 1, 0));

		glm::vec3 direction = qyaw * zAxis;

		std::cout << "initial angle = " << angle << std::endl;
		std::cout << "direction = " << direction;
		std::cout << "arccos = " << glm::acos(direction.z) << std::endl;
		std::cout << "arccos (degrees) = " << glm::degrees(glm::acos(direction.z)) << std::endl;
	}

	std::cout << std::endl;

	{
		float angle = -45.f;
		glm::vec3 zAxis{ 0, 0, 1 };
		glm::quat qyaw = glm::angleAxis(glm::radians(angle), glm::vec3(0, 1, 0));

		glm::vec3 direction = qyaw * zAxis;

		std::cout << "initial angle = " << angle << std::endl;
		std::cout << "direction = " << direction;
		std::cout << "arccos = " << glm::acos(direction.z) << std::endl;
		std::cout << "arccos (degrees) = " << glm::degrees(glm::acos(direction.z)) << std::endl;
	}

	std::cout << std::endl;

	{
		float angle = 90.f;
		glm::vec3 zAxis{ 0, 0, 1 };
		glm::quat qyaw = glm::angleAxis(glm::radians(angle), glm::vec3(0, 1, 0));

		glm::vec3 direction = qyaw * zAxis;

		std::cout << "initial angle = " << angle << std::endl;
		std::cout << "direction = " << direction;
		std::cout << "arccos = " << glm::acos(direction.z) << std::endl;
		std::cout << "arccos (degrees) = " << glm::degrees(glm::acos(direction.z)) << std::endl;
	}

	std::cout << std::endl;

	{
		float angle = -90.f;
		glm::vec3 zAxis{ 0, 0, 1 };
		glm::quat qyaw = glm::angleAxis(glm::radians(angle), glm::vec3(0, 1, 0));

		glm::vec3 direction = qyaw * zAxis;

		std::cout << "initial angle = " << angle << std::endl;
		std::cout << "direction = " << direction;
		std::cout << "arccos = " << glm::acos(direction.z) << std::endl;
		std::cout << "arccos (degrees) = " << glm::degrees(glm::acos(direction.z)) << std::endl;
	}

	std::cout << std::endl;

	{
		float angle = 135.f;
		glm::vec3 zAxis{ 0, 0, 1 };
		glm::quat qyaw = glm::angleAxis(glm::radians(angle), glm::vec3(0, 1, 0));

		glm::vec3 direction = qyaw * zAxis;

		std::cout << "initial angle = " << angle << std::endl;
		std::cout << "direction = " << direction;
		std::cout << "arccos = " << glm::acos(direction.z) << std::endl;
		std::cout << "arccos (degrees) = " << glm::degrees(glm::acos(direction.z)) << std::endl;
	}


	std::cout << std::endl;

	{
		float angle = -135.f;
		glm::vec3 zAxis{ 0, 0, 1 };
		glm::quat qyaw = glm::angleAxis(glm::radians(angle), glm::vec3(0, 1, 0));

		glm::vec3 direction = qyaw * zAxis;

		std::cout << "initial angle = " << angle << std::endl;
		std::cout << "direction = " << direction;
		std::cout << "arccos = " << glm::acos(direction.z) << std::endl;
		std::cout << "arccos (degrees) = " << glm::degrees(glm::acos(direction.z)) << std::endl;
	}

	std::cout << std::endl;

	{
		float angle = 180.f;
		glm::vec3 zAxis{ 0, 0, 1 };
		glm::quat qyaw = glm::angleAxis(glm::radians(angle), glm::vec3(0, 1, 0));

		glm::vec3 direction = qyaw * zAxis;

		std::cout << "initial angle = " << angle << std::endl;
		std::cout << "direction = " << direction;
		std::cout << "arccos = " << glm::acos(direction.z) << std::endl;
		std::cout << "arccos (degrees) = " << glm::degrees(glm::acos(direction.z)) << std::endl;
	}

	std::cout << std::endl;

	{
		float angle = -180.f;
		glm::vec3 zAxis{ 0, 0, 1 };
		glm::quat qyaw = glm::angleAxis(glm::radians(angle), glm::vec3(0, 1, 0));

		glm::vec3 direction = qyaw * zAxis;

		std::cout << "initial angle = " << angle << std::endl;
		std::cout << "direction = " << direction;
		std::cout << "arccos = " << glm::acos(direction.z) << std::endl;
		std::cout << "arccos (degrees) = " << glm::degrees(glm::acos(direction.z)) << std::endl;
	}
}

void Landfill::PrintPitchAngles()
{
	{
		float angle = 0.f;
		glm::vec3 zAxis{ 0, 0, 1 };
		glm::quat qyaw = glm::angleAxis(glm::radians(angle), glm::vec3(1, 0, 0));

		glm::vec3 direction = qyaw * zAxis;

		std::cout << "initial angle = " << angle << std::endl;
		std::cout << "direction = " << direction;
		std::cout << "arccos = " << glm::asin(direction.y) << std::endl;
		std::cout << "arccos (degrees) = " << glm::degrees(glm::asin(direction.y)) << std::endl;
	}

	std::cout << std::endl;
}

void Landfill::TestYawlCalc()
{
	float testCases[] = { 0.f, -179.99f, 179.99f, 45.f, 90.f, 135.f, -45.f, -90.f, -135.f};
	glm::vec3 zAxis{ 0, 0, 1 };

	for (float angle : testCases)
	{
		glm::quat qyaw = glm::angleAxis(glm::radians(angle), glm::vec3(0, 1, 0));
		glm::vec3 direction = qyaw * zAxis;
		float res = camera_utility::CalculateYawl(direction);

		AssertFloatEqual(angle, res, "TestYawlCalc", 1e-1f);
	}
}

void Landfill::TestPitchCalc()
{
	float testCases[] = { 0.f, -179.99f, 179.99f, 45.f, 90.f, 135.f, -45.f, -90.f, -135.f};
	glm::vec3 yAxis{ 0, 1, 0 };

	for (float angle : testCases)
	{
		glm::quat qyaw = glm::angleAxis(glm::radians(-angle), glm::vec3(1, 0, 0));
		glm::vec3 direction = qyaw * yAxis;
		float res = camera_utility::CalculatePitch(direction);

		AssertFloatEqual(angle, res, "TestPitchCalc", 1e-1f);
	}
}

void Landfill::AssertFloatEqual(float expected, float actual, std::string caption, float precision)
{
	if (!glm::epsilonEqual<float>(expected, actual, precision))
	{
		std::cout << std::format("[{}] Assertion failed: actual = {} not equal to expected = {}\n", caption, actual, expected);
		std::terminate();
	}
}