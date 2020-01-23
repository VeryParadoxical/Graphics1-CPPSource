#pragma once
#include <vector>
#include "Vector3D.h"
#include <Windows.h>

/* _100477500 Graphics I */

class Vertex
{
public:
	Vertex();
	Vertex(float x, float y, float z);
	Vertex(float x, float y, float z, Vector3D normal, COLORREF colour);
	Vertex(const Vertex& other);

	// Accessors
	float GetX() const;
	float GetY() const;
	float GetZ() const;
	float GetW() const;

	void SetX(const float x);
	void SetY(const float y);
	void SetZ(const float z);
	void SetW(const float w);

	void SetNormal(Vector3D normal);
	Vector3D GetNormal() const;

	void SetColour(COLORREF colour);
	COLORREF GetColour() const;

	void ContributeCountIncrement();
	void SetContributeCount(int value);

	int GetContributeCount() const;

	// Assignment operator
	Vertex& operator= (const Vertex& rhs);

	bool operator== (const Vertex& rhs) const;

	const Vertex operator+ (const Vertex& rhs) const;

	Vector3D CreateVector(const Vertex& other) const;

	void Dehomogenise();


private:
	float _x;
	float _y;
	float _z;
	float _w;
	Vector3D _normal = Vector3D(0,0,0);
	COLORREF _colour = COLORREF(RGB(0,0,0));
	int _contributingCount = 0;
};

