#pragma once
#include "Vector3D.h"
#include <Windows.h>
#include "Vertex.h"

/* _100477500 Graphics I */

class PointLighting
{
public:
	PointLighting();
	PointLighting(COLORREF colour, Vertex light_position, Vertex attenuationRGB);

	void SetLightIntensity(COLORREF light_intensity);
	COLORREF GetLightIntensity() const;

	void SetLightPosition(Vertex light_position);
	Vertex GetLightPosition() const;

	void SetAttenuationA(float attenuationA);
	void SetAttenuationB(float attenuationB);
	void SetAttenuationC(float attenuationC);
	void SetAttenuationABC(Vertex attenuationABC);
	float GetAttenuationA() const;
	float GetAttenuationB() const;
	float GetAttenuationC() const;
	Vertex GetAttenuationABC() const;

private:
	COLORREF _light_intensity = (RGB(0, 0, 0));
	Vertex _light_position = Vertex(0.0f, 0.0f, 0.0f);
	Vertex _attenuationABC = (Vertex(0.0f, 0.0f, 0.0f));
	PointLighting& operator=(const PointLighting& rhs);
	void Copy(const PointLighting& other);

};