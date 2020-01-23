#pragma once

/* _100477500 Graphics I */

class Vector3D
{
public:
	Vector3D(float x, float y, float z);
	~Vector3D();

	static Vector3D CrossProduct (const Vector3D v1, const Vector3D v2);
	static Vector3D Normalise(Vector3D base_vector);
	float GetLength() const;
	static float DotProduct(const Vector3D v1 , const Vector3D v2);
	


	Vector3D& operator= (const Vector3D& rhs) noexcept;
	Vector3D operator+ (const Vector3D& rhs) noexcept;

	float GetX() const;
	float GetY() const;
	float GetZ() const;




private: 
	float _x = 0.0f;
	float _y = 0.0f;
	float _z = 0.0f;

	void Copy(const Vector3D& other);

};

