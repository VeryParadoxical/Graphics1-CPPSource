#include "DirectionalLighting.h"

/* _100477500 Graphics I */

DirectionalLighting::DirectionalLighting()
{
}

DirectionalLighting::DirectionalLighting(COLORREF colour, Vector3D light_direction)
{
	_light_intensity = colour;
	_light_direction = light_direction;
}

void DirectionalLighting::SetLightIntensity(COLORREF light_intensity)
{
	_light_intensity = light_intensity;
}

COLORREF DirectionalLighting::GetLightIntensity() const
{
	return _light_intensity;
}

void DirectionalLighting::SetLightDirection(Vector3D light_direction)
{
	_light_direction = light_direction;
}

Vector3D DirectionalLighting::GetLightDirection() const
{
	return _light_direction;
}


DirectionalLighting& DirectionalLighting::operator=(const DirectionalLighting& rhs)
{

	if (this != &rhs)
	{
		Copy(rhs);
	}
	return *this;
}

void DirectionalLighting::Copy(const DirectionalLighting& other)
{
	_light_direction = other.GetLightDirection();
	_light_intensity = other.GetLightIntensity();
}
