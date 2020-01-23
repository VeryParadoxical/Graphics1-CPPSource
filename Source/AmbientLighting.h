#pragma once
#include "Vector3D.h"
#include <Windows.h>

/* _100477500 Graphics I */

class AmbientLighting
{
public:
	AmbientLighting();
	AmbientLighting(COLORREF colour, Vector3D light_direction);

	void SetLightIntensity(COLORREF light_intensity);
	COLORREF GetLightIntensity() const;

	void SetLightDirection(Vector3D light_direction);
	Vector3D GetLightDirection() const;




private:
	COLORREF _light_intensity = (RGB(0, 0, 0));
	Vector3D _light_direction = Vector3D(0, 0, 0);
	AmbientLighting& operator=(const AmbientLighting& rhs);
	void Copy(const AmbientLighting& other);

};

