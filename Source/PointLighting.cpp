#include "PointLighting.h"

/* _100477500 Graphics I */

PointLighting::PointLighting()
{
}

PointLighting::PointLighting(COLORREF colour, Vertex light_position, Vertex attenuationABC)
{
	_light_intensity = colour;
	_light_position = light_position;
	_attenuationABC = attenuationABC;
}

void PointLighting::SetLightIntensity(COLORREF light_intensity)
{
	_light_intensity = light_intensity;
}
COLORREF PointLighting::GetLightIntensity() const
{
	return _light_intensity;
}

void PointLighting::SetLightPosition(Vertex light_position)
{
	_light_position = light_position;
}
Vertex PointLighting::GetLightPosition() const
{
	return _light_position;
}

void PointLighting::SetAttenuationA(float attenuationA)
{
	_attenuationABC.SetX(attenuationA);
}

void PointLighting::SetAttenuationB(float attenuationB)
{
	_attenuationABC.SetY(attenuationB);
}

void PointLighting::SetAttenuationC(float attenuationC)
{
	_attenuationABC.SetZ(attenuationC);
}

void PointLighting::SetAttenuationABC(Vertex attenuationABC) 
{
	_attenuationABC = attenuationABC;
}

float PointLighting::GetAttenuationA() const
{
	return _attenuationABC.GetX();
}

float PointLighting::GetAttenuationB() const
{
	return _attenuationABC.GetY();
}

float PointLighting::GetAttenuationC() const
{
	return _attenuationABC.GetZ();
}

Vertex PointLighting::GetAttenuationABC() const
{
	return _attenuationABC;
}

PointLighting& PointLighting::operator=(const PointLighting& rhs)
{

	if (this != &rhs)
	{
		Copy(rhs);
	}
	return *this;
}

void PointLighting::Copy(const PointLighting& other)
{
	_light_position = other.GetLightPosition();
	_light_intensity = other.GetLightIntensity();
	_attenuationABC = other.GetAttenuationABC();
}
