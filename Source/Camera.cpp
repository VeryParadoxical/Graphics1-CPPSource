#include "Camera.h"
#include "cmath"

/* _100477500 Graphics I */

Camera::Camera()
{
	_xRotation = 0;
	_yRotation = 1;
	_zRotation = 0;
	_position = Vertex(0,0,-100);
	SetCameraMatrix();
}

Camera::Camera(float xRotation, float yRotation, float zRotation, const Vertex& position)
{
	_xRotation = xRotation;
	_yRotation = yRotation;
	_zRotation = zRotation;
	_position = position;
	SetCameraMatrix();
}



Camera::~Camera()
{
};

Matrix Camera::GetCameraMatrix()
{
	return _cameraMatrix;
}
Vertex Camera::GetPosition()
{
	return _position;
}
;

void Camera::SetCameraMatrix() 
{
	radians = static_cast<float>(_xRotation * 3.14159265359 / 180.0);
	Matrix xRotationM = {
		1, 0, 0, 0,
		0, cos(radians), sin(radians) ,0,
		0, -sin(radians), cos(radians) ,0,
		0, 0, 0, 1
	};

	radians = static_cast<float>(_yRotation * 3.14159265359 / 180.0);
	Matrix yRotationM {
		cos(radians), 0, -sin(radians), 0,
		0, 1, 0, 0,
		sin(radians), 0, cos(radians), 0,
		0, 0, 0, 1
	};
	
	radians = static_cast<float>(_zRotation * 3.14159265359 / 180.0);
	Matrix zRotationM = {
			cos(radians), sin(radians), 0, 0,
			-sin(radians), cos(radians), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
	};
	
	Matrix translationM = {
		1, 0, 0, -(_position.GetX()),
		0, 1, 0, -(_position.GetY()),
		0, 0, 1, -(_position.GetZ()),
		0, 0, 0, 1
	};
	
	_cameraMatrix = xRotationM * yRotationM * zRotationM * translationM;
}



void Camera::AlterXRotate(float x)
{
	_xRotation += x;
}

void Camera::AlterYRotate(float y)
{
	_yRotation += y;
}

void Camera::AlterZRotate(float z)
{
	_zRotation += z;
}
