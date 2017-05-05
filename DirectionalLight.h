#pragma once
#include "Light.h"

class DirectionalLight
{
private:
	Light light;
	glm::vec3 direction;

public:
	DirectionalLight();
	DirectionalLight(Light light, glm::vec3 direction);
	~DirectionalLight();

	inline const glm::vec3 GetDirection() const
	{
		return direction;
	}

	inline const Light GetBaseLight() const
	{
		return light;
	}
};