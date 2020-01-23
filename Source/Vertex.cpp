#include "Vertex.h"

/* _100477500 Graphics I */

Vertex::Vertex()
{
	_x = 0.0f;
	_y = 0.0f;
	_z = 0.0f;
	_w = 1.0f;
}

Vertex::Vertex(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
	_w = 1;
}

Vertex::Vertex(float x, float y, float z, Vector3D normal, COLORREF colour)
{
	_x = x;
	_y = y;
	_z = z;
	_w = 1;
	_normal = normal;
	_colour = colour;
}

Vertex::Vertex(const Vertex & other)
{
	_x = other.GetX();
	_y = other.GetY();
	_z = other.GetZ();
	_w = other.GetW();
	_colour = other.GetColour();
	_normal = other.GetNormal();
	_contributingCount = other.GetContributeCount();
}

float Vertex::GetX() const
{
	return _x;
}

float Vertex::GetY() const
{
	return _y;
}

float Vertex::GetZ() const
{
	return _z;
}

float Vertex::GetW() const
{
	return _w;
};

void Vertex::SetX(const float x)
{
	_x = x;
}

void Vertex::SetY(const float y)
{
	_y = y;
}

void Vertex::SetZ(const float z)
{
	_z = z;
}

void Vertex::SetW(const float w)
{
	_w = w;
}

void Vertex::SetNormal(Vector3D normal)
{
	_normal = normal;
}

Vector3D Vertex::GetNormal() const
{
	return _normal;
}

void Vertex::SetColour(COLORREF colour)
{
	_colour = colour;
}

COLORREF Vertex::GetColour() const
{
	return _colour;
}

void Vertex::ContributeCountIncrement()
{
	_contributingCount += 1;
}

void Vertex::SetContributeCount(int value)
{
	_contributingCount = value;
}

int Vertex::GetContributeCount() const
{
	return _contributingCount;
}

Vertex& Vertex::operator=(const Vertex& rhs)
{
	// Only do the assignment if we are not assigning
	// to ourselves
	if (this != &rhs)
	{
		_x = rhs.GetX();
		_y = rhs.GetY();
		_z = rhs.GetZ();
		_w = rhs.GetW();
		_colour = rhs.GetColour();
		_normal = rhs.GetNormal();
		_contributingCount = rhs.GetContributeCount();
	}
	return *this;
}

// The const at the end of the declaraion for '==" indicates that this operation does not change
// any of the member variables in this class.

bool Vertex::operator==(const Vertex& rhs) const
{
	return (_x == rhs.GetX() && _y == rhs.GetY() && _z == rhs.GetZ() && _w == rhs.GetW());
}

// You can see three different uses of 'const' here:
//
// The first const indicates that the method changes the return value, but it is not moved in memory
// The second const indicates that the parameter is passed by reference, but it is not modified
// The third const indicates that the operator does not change any of the memory variables in the class.

const Vertex Vertex::operator+(const Vertex& rhs) const
{
	return Vertex(_x + rhs.GetX(), _y + rhs.GetY(), _z + rhs.GetZ()); //+ rhs.GetW()
}

Vector3D Vertex::CreateVector(const Vertex& other) const
{

	return Vector3D(other.GetX() - _x, other.GetY() - _y, other.GetZ() - _z);
}



void Vertex::Dehomogenise()
{
	_x /= _w;
	_y /= _w;
	_z /= _w;
	_w /= _w;
}
