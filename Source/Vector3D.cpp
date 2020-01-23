#include "Vector3D.h"
#include <cmath>

/* _100477500 Graphics I */

Vector3D::Vector3D(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

Vector3D::~Vector3D()
{
}

float Vector3D::GetX() const
{
	return _x;
}

float Vector3D::GetY() const
{
	return _y;
}

float Vector3D::GetZ() const
{
	return _z;
}

float Vector3D::DotProduct(const Vector3D v1, const Vector3D v2)
{
	return ((v1.GetX() * v2.GetX()) + (v1.GetY() * v2.GetY()) + (v1.GetZ() * v2.GetZ()));
}

Vector3D Vector3D::CrossProduct(const Vector3D v1, const Vector3D v2)
{
	return Vector3D((v1.GetY() * v2.GetZ())- (v1.GetZ() * v2.GetY()), 
					(v1.GetZ() * v2.GetX()) - (v1.GetX() * v2.GetZ()),
					(v1.GetX() * v2.GetY()) - (v1.GetY() * v2.GetX()));
}

Vector3D Vector3D::Normalise(Vector3D base_vector) 
{
	float x = base_vector.GetX();
	float y = base_vector.GetY();
	float z = base_vector.GetZ();

	float magnitude = sqrt(x * x + y * y + z * z);
	return Vector3D((x / magnitude), (y / magnitude), (z / magnitude));
}

float Vector3D::GetLength() const
{
	float magnitude = sqrt(_x * _x + _y * _y + _z * _z);
	return magnitude;
}



Vector3D& Vector3D::operator=(const Vector3D& rhs) noexcept
{
	
	if (this != &rhs)
	{
	// Only do if not assigning to ourselves (remember that a = b is the same as a.operator=(b))
		Copy(rhs);
	}
	return *this;
}

Vector3D Vector3D::operator+(const Vector3D& rhs) noexcept
{
	return Vector3D (_x + rhs.GetX(), _y + rhs.GetY(), _z + rhs.GetZ() );

}

void Vector3D::Copy(const Vector3D& other)
{
	_x = other.GetX();
	_y = other.GetY();
	_z = other.GetZ();
}