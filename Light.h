#pragma once
#include <glm\glm\vec3.hpp>

class Light
{
private:
	glm::vec3 colour;
	float diffuseIntensity;

public:
	Light();
	Light(glm::vec3 color, float diffuse);
	~Light();

	void SetColour(const glm::vec3 color);

	inline const glm::vec3 GetColour() const
	{
		return colour;
	}

	void SetDiffuseIntensity(const float diffuse);
	
	inline const float GetDiffuseIntensity() const
	{
		return diffuseIntensity;
	}
};