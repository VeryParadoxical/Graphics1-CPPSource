#pragma once
#include "Vector3D.h"
#include <Windows.h>

/* _100477500 Graphics I */

class DirectionalLighting
{
public: 
	DirectionalLighting();
	DirectionalLighting(COLORREF colour, Vector3D light_direction);

	void SetLightIntensity(COLORREF light_intensity);
	COLORREF GetLightIntensity() const;

	void SetLightDirection(Vector3D light_direction);
	Vector3D GetLightDirection() const;




private:
	COLORREF _light_intensity = (RGB(0, 0, 0));
	Vector3D _light_direction = Vector3D(0, 0, 0);
	DirectionalLighting& operator=(const DirectionalLighting& rhs);
	void Copy(const DirectionalLighting& other);

};

