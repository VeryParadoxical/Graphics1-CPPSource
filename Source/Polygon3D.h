#pragma once
#include <Windows.h>
#include "Vector3D.h"
#include <vector>

class Polygon3D
{
public:
	Polygon3D();
	Polygon3D(int index0, int index1, int index2);
	~Polygon3D();

	Polygon3D(const Polygon3D& p);

	// Accessor to return index of specified vertex
	int GetIndex(int index) const;
	void SetVisibility(bool visible);
	bool GetVisibility() const;
	void SetNormal(Vector3D);
	float GetAverageZ() const;
	void SetAverageZ(float average_z);
	Vector3D GetNormal() const;
	COLORREF GetColour() const;
	void SetColour(COLORREF colour);
	Polygon3D& operator= (const Polygon3D& rhs);

private:
	Vector3D _normal = Vector3D(0.0f,0.0f,0.0f);
	int _indices[3];
	bool _visibility = true;
	float _average_z = 0.0f;
	COLORREF _colour = (RGB(0, 0, 0));
	void Copy(const Polygon3D& other);
};

