#include "DirectionalLight.h"

DirectionalLight::DirectionalLight()
{
}

DirectionalLight::DirectionalLight(Light newLight, glm::vec3 newDir)
{
	light.SetColour(newLight.GetColour());
	light.SetDiffuseIntensity(newLight.GetDiffuseIntensity());

	direction = newDir;
}

DirectionalLight::~DirectionalLight()
{
}