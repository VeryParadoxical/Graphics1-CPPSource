#pragma once
#include "Matrix.h"

/* _100477500 Graphics I */

class Camera
{
public: 
	Camera();
	Camera(float xRotation, float yRotation, float zRotation, const Vertex& position);
	~Camera();
	void SetCameraMatrix();
	Matrix GetCameraMatrix();
	Vertex GetPosition();


	void AlterXRotate(float x);
	void AlterYRotate(float y);
	void AlterZRotate(float z);

private: 
	float radians;
	float _xRotation;
	float _yRotation;
	float _zRotation;
	Vertex _position;
	Matrix _cameraMatrix;
};

