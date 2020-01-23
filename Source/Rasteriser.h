#pragma once
#include "Framework.h"
#include "Vertex.h"
#include "Matrix.h"
#include "Model.h"
#include "MD2Loader.h"
#include "Camera.h"
#include "DirectionalLighting.h"
#include "AmbientLighting.h"
#include "PointLighting.h"

class Rasteriser : public Framework
{
public: 
	//Default constructor
	bool Initialise();

	//Destructor
	~Rasteriser();

	void Render(const Bitmap &bitmap);
	void Update(const Bitmap &bitmap);

	void GeneratePerspectiveMatrix(float d, float aspectRatio);
	void GenerateViewMatrix(float d, int width, int height);

	//Model Transformation
	Matrix Translate(float translateX, float translateY, float translateZ);
	Matrix Scale(float scaleX, float scaleY, float scaleZ);
	Matrix RotateX(float radians);
	Matrix RotateY(float radians);
	Matrix RotateZ(float radians);
	Matrix TransformCombined(float angleX, float angleY, float angleZ, float scaleX, 
		float scaleY, float scaleZ, float translateX, float translateY, float translateZ);

	void DrawWireFrame(const Bitmap& bitmap);

	void DrawWireFrameCulled(const Bitmap& bitmap);

	void DrawSolidFlat(const Bitmap& bitmap);

	vector<DirectionalLighting> GetDirectionalLights();

	void AddDirectionalLights(DirectionalLighting light_source);

	void AddAmbientLights(AmbientLighting light_source);

	vector<AmbientLighting> GetAmbientLights();

	void AddPointLights(PointLighting light_source);

	vector<PointLighting> GetPointLights();


	void DrawString(const Bitmap& bitmap, LPCTSTR text);

	void MyDrawSolidFlat(const Bitmap& bitmap);
	void FillPolygonFlat(const HDC& hDc, const Vertex& v0, const Vertex& v1, const Vertex& v2, const COLORREF& colour);
	void TopFillTriangle(const HDC& hDc, const Vertex& v1, const Vertex& v2, const Vertex& v3, const COLORREF& colour);
	void BottomFillTriangle(const HDC& hDc, const Vertex& v1, const Vertex& v2, const Vertex& v3, const COLORREF& colour);

	void DrawGouraud(const Bitmap& bitmap);
	void FillPolygonGouraud(const HDC& hDc, const Vertex& v1, const Vertex& v2, const Vertex& v3);
	void TopFillGouraud(const HDC& hDc, const Vertex& v1, const Vertex& v2, const Vertex& v3, COLORREF colourv1, COLORREF colourv2, COLORREF colourv3);
	void BottomFillGouraud(const HDC& hDc, const Vertex& v1, const Vertex& v2, const Vertex& v3, COLORREF colourv1, COLORREF colourv2, COLORREF colourv3);



private:

	Model _model;

	Matrix _modelMatrix;
	Matrix _viewMatrix;
	Matrix _perspectiveMatrix;

	vector<DirectionalLighting> _directionalLights;
	vector<AmbientLighting> _ambientLights;
	vector<PointLighting> _pointLights;

	Camera _camera;
	float _rotate_x{ 0.0f };
	float _rotate_y{ 0.0f }; //By default no translation.
	float _rotate_z{ 0.0f };
	float _scale_x{ 1.0f };
	float _scale_y{ 1.0f }; //By default leave scale at 100%
	float _scale_z{ 1.0f };
	float _translate_x{ 0.0f };
	float _translate_y{ 0.0f }; //No translation by default.
	float _translate_z{ 0.0f };

	int _renderState = 0; //Controls starting point; default is  0, set to x to start with x step in render.
	float _renderSubState = 0.0f;
	int _updateState = 1; // Controls starting point; default is 1, set to 0 to avoid transformations, 2 to allow base transformations in update.
	float _updateSubState = 0.0f;

	COLORREF colourv1 =	(0,0,0);
	COLORREF colourv2 = (0,0,0);
	COLORREF colourv3 = (0,0,0);
};

