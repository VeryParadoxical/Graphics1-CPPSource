#include "Polygon3D.h"

/* _100477500 Graphics I */

Polygon3D::Polygon3D() : _indices{0}
{
}

Polygon3D::Polygon3D(int index0, int index1, int index2)
{
	_indices[0] = index0;
	_indices[1] = index1;
	_indices[2] = index2;
	_average_z = 0.0f;
	_colour = COLORREF(RGB(0,0,0)); //Set colour of each polygon.
	_visibility = true;
	_normal = Vector3D(0.0f, 0.0f, 0.0f);
}

Polygon3D::~Polygon3D()
{
}

void Polygon3D::SetVisibility(bool visible) 
{
	_visibility = visible;
}

bool Polygon3D::GetVisibility() const
{
	return _visibility;
}

void Polygon3D::SetNormal(Vector3D normal)
{
	_normal = normal;
}

float Polygon3D::GetAverageZ() const
{
	return _average_z;
}

void Polygon3D::SetAverageZ(float average_z)
{
	_average_z = average_z;
}

Vector3D Polygon3D::GetNormal() const
{
	return _normal;
}

COLORREF Polygon3D::GetColour() const
{
	return _colour;
}

void Polygon3D::SetColour(COLORREF colour)
{
	_colour = colour;
}

Polygon3D::Polygon3D(const Polygon3D& p) : _indices{ 0 }
{
	Copy(p);
}

int Polygon3D::GetIndex(int index) const
{
	return _indices[index];
}

Polygon3D& Polygon3D::operator=(const Polygon3D& rhs)
{
	if (this != &rhs)
	{
		Copy(rhs);
	}
	return *this;
}

void Polygon3D::Copy(const Polygon3D& other)
{
	_indices[0] = other.GetIndex(0);
	_indices[1] = other.GetIndex(1);
	_indices[2] = other.GetIndex(2);
	_visibility = other.GetVisibility();
	_colour = other.GetColour();
	_average_z = other.GetAverageZ();
	_normal = other.GetNormal();
}
