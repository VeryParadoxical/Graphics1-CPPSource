#include "AmbientLighting.h"

/* _100477500 Graphics I */

AmbientLighting::AmbientLighting()
{
}

AmbientLighting::AmbientLighting(COLORREF colour, Vector3D light_direction)
{
	_light_intensity = colour;
	_light_direction = light_direction;
}

void AmbientLighting::SetLightIntensity(COLORREF light_intensity)
{
	_light_intensity = light_intensity;
}

COLORREF AmbientLighting::GetLightIntensity() const
{
	return _light_intensity;
}

void AmbientLighting::SetLightDirection(Vector3D light_direction)
{
	_light_direction = light_direction;
}

Vector3D AmbientLighting::GetLightDirection() const
{
	return _light_direction;
}


AmbientLighting& AmbientLighting::operator=(const AmbientLighting& rhs)
{

	if (this != &rhs)
	{
		Copy(rhs);
	}
	return *this;
}

void AmbientLighting::Copy(const AmbientLighting& other)
{
	_light_direction = other.GetLightDirection();
	_light_intensity = other.GetLightIntensity();
}