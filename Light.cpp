#include "Light.h"

Light::Light()
{
}

Light::Light(glm::vec3 color, float diffuse)
{
	colour = color;
	diffuseIntensity = diffuse;
}

Light::~Light()
{
}

void Light::SetColour(const glm::vec3 color)
{
	colour = color;
}

void Light::SetDiffuseIntensity(const float diffuse)
{
	diffuseIntensity = diffuse;
}