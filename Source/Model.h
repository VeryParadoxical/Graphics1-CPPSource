#pragma once
#include <vector>
#include "Vertex.h"
#include "Matrix.h"
#include "Polygon3D.h"
#include "Vector3D.h"
#include "DirectionalLighting.h"
#include "AmbientLighting.h"
#include "PointLighting.h"

/* _100477500 Graphics I */

class Model
{


public:
	Model();
	~Model();

	// Accessors
	const std::vector<Polygon3D>&		GetPolygons();
	const std::vector<Vertex>&			GetVertices();
	const std::vector<Vertex>&			GetTransformedVertices();
	size_t								GetPolygonCount() const;
	size_t								GetBaseVertexCount() const;
	size_t								GetTransformedVertexCount() const;
	void								AddVertex(float x, float y, float z);
	void 								AddPolygon(int i0, int i1, int i2);
	void                                ApplyTransformToLocalVertices(const Matrix& transform);
	void                                ApplyTransformToTransformedVertices(const Matrix& transform);
	void								DehomogeniseModel();
	void								Sort();
	void								BackfaceCulling(const Vertex& cameraPosition);
	float								GetKA_Red();
	float								GetKA_Green();
	float								GetKA_Blue();
	float								GetKD_Red();
	float								GetKD_Green();
	float								GetKD_Blue();
	float								GetKS_Red();
	float								GetKS_Green();
	float								GetKS_Blue();
	void								CalculateVertexNormals();

	void								CalculateLightingAmbient(std::vector<AmbientLighting> ambient_lights);
	void								CalculateLightingDirectional(std::vector<DirectionalLighting> directional_lights);
	void								CalculateLightingPoint(std::vector<PointLighting> point_lights);
	int									RGBClamping(int value);

	void								CalculateLightingDirectionalVertices(std::vector<DirectionalLighting> directional_lights);
	void								CalculateLightingPointVertices(std::vector<PointLighting> point_lights);
	

private:
	
	std::vector<Polygon3D> _polygons;
	std::vector<Vertex> _vertices;
	std::vector<Vertex> _transformedVertices;
	std::vector<DirectionalLighting> _directionalLights;
	std::vector<AmbientLighting> _ambientLights;
	
	COLORREF _temp = (RGB(0,0,0));
	COLORREF _total = (RGB(0,0,0));

	//Ambient
	float _ka_red = 0.25f;
	float _ka_green = 0.25f;
	float _ka_blue = 0.25f;

	//Directional / Point
	float _kd_red = 0.5f;
	float _kd_green = 0.5f;
	float _kd_blue = 0.5f;

	//Spot (not point)
	float _ks_red = 1.0f;
	float _ks_green = 1.0f;
	float _ks_blue = 1.0f;

	float _dotResult = 0;
};