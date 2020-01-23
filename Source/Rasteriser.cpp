#include "Rasteriser.h"
#include <cmath>

/* _100477500 Graphics I */

Rasteriser app;

bool Rasteriser::Initialise() 
{ 
	if (!MD2Loader::LoadModel("marvin.md2", _model,
		&Model::AddPolygon,
		&Model::AddVertex)) 
	{
		
		return false; 
	}
	_camera = Camera{ 0.0f, 0.0f, 0.0f, Vertex{ 0.0f, 0.0f, -50.0f } }; 
	AddAmbientLights(AmbientLighting(COLORREF(RGB(100, 30, 30)), Vector3D(-10, 0, -10)));
	AddDirectionalLights(DirectionalLighting(COLORREF(RGB(150, 100, 100)), Vector3D(-10, 0, -10)));
	AddPointLights(PointLighting(COLORREF(RGB(90, 90, 90)), Vertex(0.0f, 0.0f, -50.0f), Vertex(0.0f,1.0f,0.0f)));
	return true;
}

Rasteriser::~Rasteriser() 
{
};




void Rasteriser::Update(const Bitmap& bitmap)
{
	GeneratePerspectiveMatrix(1.0, static_cast<float>(bitmap.GetWidth()) / static_cast<float>(bitmap.GetHeight()));
	GenerateViewMatrix(1, bitmap.GetWidth(), bitmap.GetHeight());

	if (_updateState == 1)
	{
		if (_updateSubState < 270) //Rotate
		{
			if (_updateSubState < 90) //X rotation
			{
				_rotate_x += 1.0f;
				_rotate_y = 0.0f;
				_rotate_z = 0.0f;
			}
			else if (_updateSubState < 180) //Y Rotation
			{
				_rotate_x = 0.0f;
				_rotate_y += 1.0f;
				_rotate_z = 0.0f;
			}
			else if (_updateSubState < 269) //Z Rotation
			{
				_rotate_x = 0.0f;
				_rotate_y = 0.0f;
				_rotate_z += 1.0f;
			}
			else
			{
				_rotate_x = 0.0f;
				_rotate_y = 90.0f;
				_rotate_z = 0.0f;
			}
		}
		else if (_updateSubState < 540)
		{
			if (_updateSubState < 360) //X translate
			{
				_translate_x += 0.5;
				_translate_y = 0.0f;
				_translate_z = 0.0f;
			}
			else if (_updateSubState < 450) //Y translate
			{
				_translate_x = 0.0f;
				_translate_y += 0.5f;
				_translate_z = 0.0f;
			}
			else if (_updateSubState < 539) //Z translate
			{
				_translate_x = 0.0f;
				_translate_y = 0.0f;
				_translate_z += 0.5f;
			}
			else 
			{
				_translate_x = 0.0f;
				_translate_y = 0.0f;
				_translate_z = 0.0f;
			}
		}
		else if (_updateSubState < 810)
		{
			if (_updateSubState < 630) //x scaling
			{
				_scale_x += 0.025f;
				_scale_y = 1.0f;
				_scale_z = 1.0f;
			}
			else if (_updateSubState < 720) //y scaling
			{
				_scale_x = 1.0f;
				_scale_y += 0.025f;
				_scale_z = 1.0f;
			}
			else if (_updateSubState < 809) //z scaling
			{
				_scale_x = 1.0f;
				_scale_y = 1.0f;
				_scale_z += 0.025f;
			}
			else
			{
				_scale_x = 1.0f;
				_scale_y = 1.0f;
				_scale_z = 1.0f;
			}
		}
		else
		{
			//Just perform X,Y,Z rotation as normal.
			_rotate_x = 0.0f;
			_rotate_y = 0.0f;
			_rotate_z = 0.0f;
			_renderState = 1;
			_renderSubState = 0;
			_updateState = 2;
		}
		_updateSubState += 1.0f; // Change to alter switching speed in update
	}
	else if (_updateState == 2)
	{
		if (_renderState == 1)
		{
			_rotate_x += 0.75f;
			_rotate_y += 0.75f;
			_rotate_z += 0.75f;
		}
		else
		{
			//These control the rotation after the base transformations demonstration.
			_rotate_x = 0.0f; 
			_rotate_y += 0.75f; //Change values here to cause rotation after initial demonstration.
			_rotate_z = 0.0f; 
		}
	}
	_modelMatrix = TransformCombined(static_cast<float>(_rotate_x * 3.14159265359 / 180.0), (static_cast<float>(_rotate_y * 3.14159265359 / 180.0)),
									static_cast<float>(_rotate_z * 3.14159265359 / 180.0),_scale_x,_scale_y,_scale_z,_translate_x,_translate_y, _translate_z);
}



void Rasteriser::Render(const Bitmap& bitmap)
{
	bitmap.Clear(RGB(100, 100, 100));

	if (_updateState == 1)
	{		
		//Base wireframe pipeline for scaling, rotating, and translating demonstration.
		_model.ApplyTransformToLocalVertices(_modelMatrix);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.ApplyTransformToTransformedVertices(_perspectiveMatrix);
		_model.DehomogeniseModel();
		_model.ApplyTransformToTransformedVertices(_viewMatrix);
		DrawWireFrame(bitmap);

		if (_updateSubState < 90)
		{
			DrawString(bitmap, L"X Rotation");
		}
		else if (_updateSubState < 180)
		{
			DrawString(bitmap, L"Y Rotation");
		}
		else if (_updateSubState < 269)
		{
			DrawString(bitmap, L"Z Rotation");
		}
		else if (_updateSubState < 360)
		{
			DrawString(bitmap, L"X Translation");
		}
		else if (_updateSubState < 450) 
		{
			DrawString(bitmap, L"Y Translation");
		}
		else if (_updateSubState < 539)
		{
			DrawString(bitmap, L"Z Translation");
		}
		else if (_updateSubState < 630)
		{
			DrawString(bitmap, L"X Scaling");
		}
		else if (_updateSubState < 720)
		{
			DrawString(bitmap, L"Y Scaling");
		}
		else if (_updateSubState < 809)
		{
			DrawString(bitmap, L"Z Scaling");
		}
	}
	else if (_renderState == 1)
	{
		if (_renderSubState < 190)
		{
			_model.ApplyTransformToLocalVertices(_modelMatrix);
			_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
			_model.ApplyTransformToTransformedVertices(_perspectiveMatrix);
			_model.DehomogeniseModel();
			_model.ApplyTransformToTransformedVertices(_viewMatrix);
			DrawWireFrame(bitmap);
			DrawString(bitmap, L"Wireframe + Full Rotation");
		}
		else
		{
			_renderSubState = 0;
			_renderState += 1;
		}
	}
	else if (_renderState == 2)
	{
		if (_renderSubState < 190)
		{
			_model.ApplyTransformToLocalVertices(_modelMatrix);
			_model.BackfaceCulling(_camera.GetPosition());
			_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
			_model.ApplyTransformToTransformedVertices(_perspectiveMatrix);
			_model.DehomogeniseModel();
			_model.ApplyTransformToTransformedVertices(_viewMatrix);
			DrawWireFrameCulled(bitmap);
			DrawString(bitmap, L"Wireframe Culled");
		}
		else
		{
			_renderSubState = 0;
			_renderState += 1;
		}
	}
	else if (_renderState == 3)
	{
		if (_renderSubState < 250)
		{
			_model.ApplyTransformToLocalVertices(_modelMatrix);
			_model.BackfaceCulling(_camera.GetPosition());
			_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
			_model.Sort();
			_model.ApplyTransformToTransformedVertices(_perspectiveMatrix);
			_model.DehomogeniseModel();
			_model.ApplyTransformToTransformedVertices(_viewMatrix);
			DrawWireFrameCulled(bitmap);
			DrawString(bitmap, L"Wireframe Culled + Sorted");
		}
		else
		{
			_renderSubState = 0;
			_renderState += 1;
		}
	}
	else if (_renderState == 4) 
	{
		if (_renderSubState < 250)
		{
			_model.ApplyTransformToLocalVertices(_modelMatrix);
			_model.BackfaceCulling(_camera.GetPosition()); 
			_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
			_model.Sort();
			_model.ApplyTransformToTransformedVertices(_perspectiveMatrix);
			_model.DehomogeniseModel();
			_model.ApplyTransformToTransformedVertices(_viewMatrix);
			DrawSolidFlat(bitmap);
			DrawString(bitmap, L"Solid Flat");
		}
		else
		{
			_renderSubState = 0;
			_renderState += 1;
		}
	}
	else if (_renderState == 5)
	{
		if (_renderSubState < 190)
		{
			_model.ApplyTransformToLocalVertices(_modelMatrix);
			_model.BackfaceCulling(_camera.GetPosition());
			_model.CalculateLightingDirectional(_directionalLights);
			_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
			_model.Sort();
			_model.ApplyTransformToTransformedVertices(_perspectiveMatrix);
			_model.DehomogeniseModel();
			_model.ApplyTransformToTransformedVertices(_viewMatrix);
			DrawSolidFlat(bitmap);
			DrawString(bitmap, L"Solid Flat + Directional Lighting");
		}
		else
		{
			_renderSubState = 0;
			_renderState += 1;
		}
	}
	else if (_renderState == 6)
	{
		if (_renderSubState < 250)
		{
			_model.ApplyTransformToLocalVertices(_modelMatrix);
			_model.BackfaceCulling(_camera.GetPosition());
			_model.CalculateLightingAmbient(_ambientLights);
			_model.CalculateLightingDirectional(_directionalLights);
			_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
			_model.Sort();
			_model.ApplyTransformToTransformedVertices(_perspectiveMatrix);
			_model.DehomogeniseModel();
			_model.ApplyTransformToTransformedVertices(_viewMatrix);
			DrawSolidFlat(bitmap);
			DrawString(bitmap, L"Solid Flat + Directional + Ambient");
		}
		else
		{
			_renderSubState = 0;
			_renderState += 1;
		}
	}
	else if (_renderState == 7)
	{
	if (_renderSubState < 250)
	{
		_model.ApplyTransformToLocalVertices(_modelMatrix);
		_model.BackfaceCulling(_camera.GetPosition());
		_model.CalculateLightingAmbient(_ambientLights);
		_model.CalculateLightingDirectional(_directionalLights);
		_model.CalculateLightingPoint(_pointLights);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_perspectiveMatrix);
		_model.DehomogeniseModel();
		_model.ApplyTransformToTransformedVertices(_viewMatrix);
		DrawSolidFlat(bitmap);
		DrawString(bitmap, L"Solid Flat + Directional + Ambient + Point ");
	}
	else
	{
		_renderSubState = 0;
		_renderState += 1;
	}
	}
	else if (_renderState == 8)
	{
	if (_renderSubState < 190)
	{
		_model.ApplyTransformToLocalVertices(_modelMatrix);
		_model.BackfaceCulling(_camera.GetPosition());
		_model.CalculateLightingAmbient(_ambientLights);
		_model.CalculateLightingDirectional(_directionalLights);
		_model.CalculateLightingPoint(_pointLights);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_perspectiveMatrix);
		_model.DehomogeniseModel();
		_model.ApplyTransformToTransformedVertices(_viewMatrix);
		MyDrawSolidFlat(bitmap);
		DrawString(bitmap, L"My Solid Flat + Directional + Ambient + Point ");
	}
	else
	{
		_renderSubState = 0;
		_renderState += 1;
	}
	}
	else if (_renderState == 9)
	{
	if (_renderSubState < 190)
	{
		_model.ApplyTransformToLocalVertices(_modelMatrix);
		_model.BackfaceCulling(_camera.GetPosition());
		_model.CalculateVertexNormals();
		_model.CalculateLightingAmbient(_ambientLights);
		_model.CalculateLightingDirectionalVertices(_directionalLights);
		_model.CalculateLightingPointVertices(_pointLights);
		_model.ApplyTransformToTransformedVertices(_camera.GetCameraMatrix());
		_model.Sort();
		_model.ApplyTransformToTransformedVertices(_perspectiveMatrix);
		_model.DehomogeniseModel();
		_model.ApplyTransformToTransformedVertices(_viewMatrix);
		DrawGouraud(bitmap);
		DrawString(bitmap, L"Gouraud + Directional + Ambient + Point ");
	}
	else
	{
		_renderSubState = 0;
		_renderState += 1;
	}
	}
	else
	{
		//Values reset to allow this to loop without use of while.
		_renderState = 0;
		_renderSubState = 0;
		_updateState = 1;
		_updateSubState = 0;

		_rotate_x = 0.0f;
		_rotate_y = 0.0f; //By default no translation.
		_rotate_z = 0.0f;
		_scale_x = 1.0f;
		_scale_y = 1.0f; //By default leave scale at 100%
		_scale_z = 1.0f;
		_translate_x = 0.0f;
		_translate_y = 0.0f; //No translation by default.
		_translate_z = 0.0f;
	}
	_renderSubState += 0.75f; //Change state switching speed
}


void Rasteriser::DrawWireFrame(const Bitmap& bitmap)
{
	HDC hDc = bitmap.GetDC();

	const vector<Polygon3D>& polygons = _model.GetPolygons();
	const vector<Vertex>& vertices = _model.GetTransformedVertices();

	for (size_t i = 0; i < _model.GetPolygonCount(); i++) 
	{
		const Polygon3D& polygon = polygons[i];

		MoveToEx(hDc, static_cast<int>(vertices[polygon.GetIndex(2)].GetX()), static_cast<int>(vertices[polygon.GetIndex(2)].GetY()), NULL);

		HPEN hPen = CreatePen(PS_SOLID, 1, COLORREF(RGB(0,255,0)));
		HGDIOBJ oldPen = SelectObject(hDc, hPen);

		LineTo(hDc, static_cast<int>(vertices[polygon.GetIndex(0)].GetX()), static_cast<int>(vertices[polygon.GetIndex(0)].GetY()));
		LineTo(hDc, static_cast<int>(vertices[polygon.GetIndex(1)].GetX()), static_cast<int>(vertices[polygon.GetIndex(1)].GetY()));
		LineTo(hDc, static_cast<int>(vertices[polygon.GetIndex(2)].GetX()), static_cast<int>(vertices[polygon.GetIndex(2)].GetY()));

		SelectObject(hDc, oldPen);
		DeleteObject(hPen);
	}
}


void Rasteriser::DrawWireFrameCulled(const Bitmap& bitmap)
{
	HDC hDc = bitmap.GetDC();

	const vector<Polygon3D>& polygons = _model.GetPolygons();
	const vector<Vertex>& vertices = _model.GetTransformedVertices();

	for (size_t i = 0; i < _model.GetPolygonCount(); i++)
	{
		const Polygon3D& polygon = polygons[i];

		if (polygon.GetVisibility()) {

			HPEN hPen = CreatePen(PS_SOLID, 1, COLORREF(RGB(0, 255, 0)));
			HGDIOBJ oldPen = SelectObject(hDc, hPen);

			MoveToEx(hDc, static_cast<int>(vertices[polygon.GetIndex(2)].GetX()), static_cast<int>(vertices[polygon.GetIndex(2)].GetY()), NULL);
			LineTo(hDc, static_cast<int>(vertices[polygon.GetIndex(0)].GetX()), static_cast<int>(vertices[polygon.GetIndex(0)].GetY()));
			LineTo(hDc, static_cast<int>(vertices[polygon.GetIndex(1)].GetX()), static_cast<int>(vertices[polygon.GetIndex(1)].GetY()));
			LineTo(hDc, static_cast<int>(vertices[polygon.GetIndex(2)].GetX()), static_cast<int>(vertices[polygon.GetIndex(2)].GetY()));

			SelectObject(hDc, oldPen);
			DeleteObject(hPen);
		}
	}
}


void Rasteriser::DrawSolidFlat(const Bitmap& bitmap)
{
	HDC hDc = bitmap.GetDC();

	const vector<Polygon3D>& polygons = _model.GetPolygons();
	const vector<Vertex>& vertices = _model.GetTransformedVertices();
	POINT points[3];

	for (size_t i = 0; i < _model.GetPolygonCount(); i++) 
	{
		const Polygon3D& polygon = polygons[i];

		if (polygon.GetVisibility())
		{
			for (int k = 0; k < 3; k++)
			{
				points[k].x = (long)vertices[polygons[i].GetIndex(k)].GetX();
				points[k].y = (long)vertices[polygons[i].GetIndex(k)].GetY();

			}
			
			HPEN hPen = CreatePen(PS_SOLID, 1, polygon.GetColour()); //Replace polygon.GetColour() with RBG(0,0,0) for black lines for each polygon. Looks way nicer.
			HGDIOBJ oldPen = SelectObject(hDc, hPen);
			HBRUSH brush = CreateSolidBrush(polygon.GetColour());
			HGDIOBJ old_brush = SelectObject(hDc, brush);

			Polygon(hDc, points, 3);

			SelectObject(hDc, oldPen);
			DeleteObject(hPen);
			SelectObject(hDc, old_brush);
			DeleteObject(brush);
		}	
	}
}


void Rasteriser::MyDrawSolidFlat(const Bitmap& bitmap)
{
	HDC hDc = bitmap.GetDC();

	const vector<Polygon3D>& polygons = _model.GetPolygons();
	const vector<Vertex>& vertices = _model.GetTransformedVertices();

	for (size_t i = 0; i < _model.GetPolygonCount(); i++)
	{
		const Polygon3D& polygon = polygons[i];

		if (polygon.GetVisibility())
		{
			Vertex temp;
			Vertex v1 = vertices[polygon.GetIndex(0)];
			Vertex v2 = vertices[polygon.GetIndex(1)]; //Using v1-3 rather than 0-2 to make it  easier on my head when ordering.
			Vertex v3 = vertices[polygon.GetIndex(2)];

			//Order the 3 vertices such that v3 > v2 > v1
			if (v1.GetY() > v2.GetY())
			{
				temp = v1;
				v1 = v2;
				v2 = temp;
			}
			if (v1.GetY() > v3.GetY())
			{
				temp = v1;
				v1 = v3;
				v3 = temp;
			}
			if (v2.GetY() > v3.GetY())
			{
				temp = v2;
				v2 = v3;
				v3 = temp;
			}
			//Pass in the 3 vertices for each polygon, FillPolygonFlat handles the rest including drawing to bitmap etc.
			FillPolygonFlat(hDc, v1, v2, v3, polygons[i].GetColour());
		}
	}
}


void Rasteriser::FillPolygonFlat(const HDC& hDc, const Vertex& v1, const Vertex& v2, const Vertex& v3, const COLORREF& colour)
{
	HPEN hPen = CreatePen(PS_SOLID, 1, colour);
	HGDIOBJ oldPen = SelectObject(hDc, hPen);

	if (v2.GetY() == v3.GetY()) // Bottom flat triangle 
	{
		BottomFillTriangle(hDc, v1, v2, v3, colour);
	}

	else if (v1.GetY() == v2.GetY()) // Top flat triangle 
	{
		TopFillTriangle(hDc, v1, v2, v3, colour);
	}
	else	// Split triangle into top and bottom triangles
	{
		Vertex v4(v1.GetX() + (v2.GetY() - v1.GetY()) / (v3.GetY() - v1.GetY()) * (v3.GetX() - v1.GetX()), v2.GetY(), v2.GetZ());

		// Ensure line will draw in the correct direction
		if (v2.GetX() > v4.GetX())
		{
			BottomFillTriangle(hDc, v1, v4, v2, colour);
			TopFillTriangle(hDc, v4, v2, v3, colour);
		}
		else
		{
			BottomFillTriangle(hDc, v1, v2, v4, colour);
			TopFillTriangle(hDc, v2, v4, v3, colour);
		}
	}
	SelectObject(hDc, oldPen);
	DeleteObject(hPen);
}


void Rasteriser::TopFillTriangle(const HDC& hDc, const Vertex& v1, const Vertex& v2, const Vertex& v3, const COLORREF& colour) // Top to bottom drawing of top triangle.
{
	float slope1 = (v3.GetX() - v1.GetX()) / (v3.GetY() - v1.GetY());
	float slope2 = (v3.GetX() - v2.GetX()) / (v3.GetY() - v2.GetY());

	float currentx1 = v3.GetX();
	float currentx2 = v3.GetX() + 0.5f;

	for (float scanlineY = v3.GetY(); scanlineY > v1.GetY(); scanlineY--)
	{
		for (float xPosition = ceil(currentx1); xPosition < currentx2; xPosition++)
		{
			SetPixel(hDc, int(xPosition), int(scanlineY), colour);
		}
		currentx1 -= slope1;
		currentx2 -= slope2;
	}
}


void Rasteriser::BottomFillTriangle(const HDC& hDc, const Vertex& v1, const Vertex& v2, const Vertex& v3, const COLORREF& colour) // Bottom to top drawing of bottom triangle.
{
	float slope1 = (v2.GetX() - v1.GetX()) / (v2.GetY() - v1.GetY());
	float slope2 = (v3.GetX() - v1.GetX()) / (v3.GetY() - v1.GetY());

	float currentx1 = v1.GetX();
	float currentx2 = v1.GetX() + 0.5f;

	for (float scanlineY = v1.GetY(); scanlineY <= v2.GetY(); scanlineY++) // For line in poly while less than last line 
	{
		for (float xPosition = ceil(currentx1); xPosition < currentx2; xPosition++)
		{
			SetPixel(hDc, int(xPosition), int(scanlineY), colour);
		}
		currentx1 += slope1;
		currentx2 += slope2;
	}
}


void Rasteriser::DrawGouraud(const Bitmap& bitmap)
{
	HDC hDc = bitmap.GetDC();

	const vector<Polygon3D>& polygons = _model.GetPolygons();
	const vector<Vertex>& vertices = _model.GetTransformedVertices();

	for (size_t i = 0; i < _model.GetPolygonCount(); i++)
	{
		const Polygon3D& polygon = polygons[i];

		if (polygon.GetVisibility())
		{
			Vertex temp;
			Vertex v1 = vertices[polygon.GetIndex(0)];
			Vertex v2 = vertices[polygon.GetIndex(1)]; //Using v1-3 rather than 0-2 to make it  easier on my head when ordering.
			Vertex v3 = vertices[polygon.GetIndex(2)];

			//Order the 3 vertices such that v3 > v2 > v1
			if (v1.GetY() > v2.GetY())
			{
				temp = v1;
				v1 = v2;
				v2 = temp;
			}
			if (v1.GetY() > v3.GetY())
			{
				temp = v1;
				v1 = v3;
				v3 = temp;
			}
			if (v2.GetY() > v3.GetY())
			{
				temp = v2;
				v2 = v3;
				v3 = temp;
			}
			FillPolygonGouraud(hDc, v1, v2, v3);
		}
	}
}


void Rasteriser::FillPolygonGouraud(const HDC& hDc, const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
	colourv1 = v1.GetColour();
	colourv2 = v2.GetColour();
	colourv3 = v3.GetColour();

	if (v2.GetY() == v3.GetY()) // Bottom flat triangle 
	{
		BottomFillGouraud(hDc, v1, v2, v3, colourv1, colourv2, colourv3);
	}

	else if (v1.GetY() == v2.GetY()) // Top flat triangle 
	{
		TopFillGouraud(hDc, v1, v2, v3, colourv1, colourv2, colourv3);
	}
	else	// Split triangle into top and bottom triangles
	{
		Vertex v4(v1.GetX() + (v2.GetY() - v1.GetY()) / (v3.GetY() - v1.GetY()) * (v3.GetX() - v1.GetX()), v2.GetY(), v2.GetZ());

		float cBlue = GetBValue(colourv1) + ((float)(v2.GetY() - v1.GetY()) / (float)(v3.GetY() - v1.GetY())) * (GetBValue(colourv3) - GetBValue(colourv1));
		float cRed = GetRValue(colourv1) + ((float)(v2.GetY() - v1.GetY()) / (float)(v3.GetY() - v1.GetY())) * (GetRValue(colourv3) - GetRValue(colourv1));
		float cGreen = GetGValue(colourv1) + ((float)(v2.GetY() - v1.GetY()) / (float)(v3.GetY() - v1.GetY())) * (GetGValue(colourv3) - GetGValue(colourv1));
		COLORREF colourv4 = COLORREF(RGB((int)cRed, (int)cGreen, (int)cBlue));

		// Ensure line will draw in the correct direction
		if (v2.GetX() > v4.GetX())
		{
			BottomFillGouraud(hDc, v1, v4, v2, colourv1, colourv2, colourv3);
			TopFillGouraud(hDc, v4, v2, v3, colourv1, colourv2, colourv3);
		}
		else
		{
			BottomFillGouraud(hDc, v1, v2, v4, colourv1, colourv2, colourv4);
			TopFillGouraud(hDc, v2, v4, v3, colourv1, colourv4, colourv3);
		}
	}
}

void Rasteriser::TopFillGouraud(const HDC& hDc, const Vertex& v1, const Vertex& v2, const Vertex& v3, COLORREF colourv1, COLORREF colourv2, COLORREF colourv3) // Top to bottom drawing of top triangle.
{
	float slope1 = (v3.GetX() - v1.GetX()) / (v3.GetY() - v1.GetY());
	float slope2 = (v3.GetX() - v2.GetX()) / (v3.GetY() - v2.GetY());

	float currentx1 = v3.GetX();
	float currentx2 = v3.GetX() + 0.5f;

	/* get the change of color components along edge (v3,v1) */
	float v3v1Diff = (float)(v3.GetY() - v1.GetY());
	float colorSlopeBlue1 = float((GetBValue(colourv3)- GetBValue(colourv1)) / v3v1Diff);
	float colorSlopeRed1 = (float)((GetRValue(colourv3) - GetRValue(colourv1)) / v3v1Diff);
	float colorSlopeGreen1 = (float)((GetGValue(colourv3) - GetGValue(colourv1))/ v3v1Diff);

	/* get the change of color components along edge (v3,v2) */
	float v3v2Diff = (float)(v3.GetY() - v2.GetY());
	float colorSlopeBlue2 = (float)((GetBValue(colourv3) - GetBValue(colourv2)) / v3v2Diff);
	float colorSlopeRed2 = (float)((GetRValue(colourv3) - GetRValue(colourv2)) / v3v2Diff);
	float colorSlopeGreen2 = (float)((GetGValue(colourv3) - GetGValue(colourv2)) / v3v2Diff);

	/* set starting values */
	float cBlue1 = GetBValue(colourv3);
	float cRed1 = GetRValue(colourv3);
	float cGreen1 = GetGValue(colourv3);
	float cBlue2 = GetBValue(colourv3);
	float cRed2 = GetRValue(colourv3);
	float cGreen2 = GetGValue(colourv3);

	/* as we will do not fill in a complete line using fillrect but instead
	 * we will loop over all pixels of a horizontal line, we need a predefined
	 * direction -> choose left to right. This means that x1 must be the smaller
	 * compared to x2 so slope1 must be smaller than slope2. If not we gonna
	 * swap it here.
	 */
	if (slope1 < slope2)
	{
		float slopeTmp = slope1;
		slope1 = slope2;
		slope2 = slopeTmp;

		slopeTmp = colorSlopeRed1;
		colorSlopeRed1 = colorSlopeRed2;
		colorSlopeRed2 = slopeTmp;

		slopeTmp = colorSlopeGreen1;
		colorSlopeGreen1 = colorSlopeGreen2;
		colorSlopeGreen2 = slopeTmp;

		slopeTmp = colorSlopeBlue1;
		colorSlopeBlue1 = colorSlopeBlue2;
		colorSlopeBlue2 = slopeTmp;
	}

	for (float scanlineY = v3.GetY(); scanlineY > v1.GetY(); scanlineY--)
	{
		for (float xPosition = ceil(currentx1); xPosition < currentx2; xPosition++)
		{
			float t = (xPosition - currentx1) / (currentx2 - currentx1);

			int red = (int)((1 - t) * cRed1 + t * cRed2);
			int green = (int)((1 - t) * cGreen1 + t * cGreen2);
			int blue = (int)((1 - t) * cBlue1 + t * cBlue2);
			SetPixel(hDc, int(xPosition), int(scanlineY), COLORREF(RGB(red, green, blue))); //work out pixel colour and set it 
		}
		/* get new x-coordinate of endpoints of horizontal line */
		currentx1 -= slope1;
		currentx2 -= slope2;
		/* get new color of left endpoint of horizontal line */
		cRed1 -= colorSlopeRed1;
		cGreen1 -= colorSlopeGreen1;
		cBlue1 -= colorSlopeBlue1;
		/* get new color of right endpoint of horizontal line */
		cRed2 -= colorSlopeRed2;
		cGreen2 -= colorSlopeGreen2;
		cBlue2 -= colorSlopeBlue2;
	}

}


void Rasteriser::BottomFillGouraud(const HDC& hDc, const Vertex& v1, const Vertex& v2, const Vertex& v3, COLORREF colourv1, COLORREF colourv2, COLORREF colourv3) // Bottom to top drawing of bottom triangle.
{
	float slope1 = (v2.GetX() - v1.GetX()) / (v2.GetY() - v1.GetY());
	float slope2 = (v3.GetX() - v1.GetX()) / (v3.GetY() - v1.GetY());

	float currentx1 = v1.GetX();
	float currentx2 = v1.GetX() + 0.5f;

	/* get the change of color components along edge (v2,v1) */
	float v2v1Diff = (float)(v2.GetY() - v1.GetY());
	float colorSlopeBlue1 = (float)((GetBValue(colourv2) - GetBValue(colourv1)) / v2v1Diff);
	float colorSlopeRed1 = (float)((GetRValue(colourv2)- GetRValue(colourv1)) / v2v1Diff);
	float colorSlopeGreen1 = (float)((GetGValue(colourv2) - GetGValue(colourv1)) / v2v1Diff);
	/* get the change of color components along edge (v3,v1) */
	float v3v1Diff = (float)((v3.GetY() - v1.GetY()));
	float colorSlopeBlue2 = (float)((GetBValue(colourv3) - GetBValue(colourv1)) / v3v1Diff);
	float colorSlopeRed2 = (float)((GetRValue(colourv3) - GetRValue(colourv1)) / v3v1Diff);
	float colorSlopeGreen2 = (float)((GetGValue(colourv3) - GetGValue(colourv1)) / v3v1Diff);
	/* get starting values */
	float cBlue1 = GetBValue(colourv1);
	float cRed1 = GetRValue(colourv1);
	float cGreen1 = GetGValue(colourv1);
	float cBlue2 = GetBValue(colourv1);
	float cRed2 = GetRValue(colourv1);
	float cGreen2 = GetGValue(colourv1);

	/* as we will do not fill in a complete line using fillrect but instead
	 * we will loop over all pixels of a horizontal line, we need a predefined
	 * direction -> choose left to right. This means that x1 must be the smaller
	 * compared to x2 so slope1 must be smaller than slope2. If not we gonna
	 * swap it here. Of course we have also to swap the colors of both line endpoints.
	 */
	if (slope2 < slope1)
	{
		float slopeTmp = slope1;
		slope1 = slope2;
		slope2 = slopeTmp;

		slopeTmp = colorSlopeRed1;
		colorSlopeRed1 = colorSlopeRed2;
		colorSlopeRed2 = slopeTmp;

		slopeTmp = colorSlopeGreen1;
		colorSlopeGreen1 = colorSlopeGreen2;
		colorSlopeGreen2 = slopeTmp;

		slopeTmp = colorSlopeBlue1;
		colorSlopeBlue1 = colorSlopeBlue2;
		colorSlopeBlue2 = slopeTmp;
	}

	for (float scanlineY = v1.GetY(); scanlineY <= v2.GetY(); scanlineY++) // For line in poly while less than last line 
	{
		for (float xPosition = ceil(currentx1); xPosition < currentx2; xPosition++)
		{
			float t = (xPosition - currentx1) / (currentx2 - currentx1);

			int red = (int)((1 - t) * cRed1 + t * cRed2);
			int green = (int)((1 - t) * cGreen1 + t * cGreen2);
			int blue = (int)((1 - t) * cBlue1 + t * cBlue2);
			SetPixel(hDc, int(xPosition), int(scanlineY), COLORREF(RGB(red, green, blue)));
		}
		/* get new x-coordinate of endpoints of horizontal line */
		currentx1 += slope1;
		currentx2 += slope2;
		/* get new color of left endpoint of horizontal line */
		cRed1 += colorSlopeRed1;
		cGreen1 += colorSlopeGreen1;
		cBlue1 += colorSlopeBlue1;
		/* get new color of right endpoint of horizontal line */
		cRed2 += colorSlopeRed2;
		cGreen2 += colorSlopeGreen2;
		cBlue2 += colorSlopeBlue2;
	}
}




void Rasteriser::GeneratePerspectiveMatrix(float d, float aspectRatio)
{
	_perspectiveMatrix = Matrix{ d / aspectRatio, 0, 0, 0,
								0, d, 0, 0,
								0, 0, d, 0,
								0, 0, 1, 0 };
}

void Rasteriser::GenerateViewMatrix(float d, int width, int height)
{
	_viewMatrix = { static_cast<float>(width) / 2, 0, 0, static_cast<float>(width) / 2,
					0, static_cast<float>(-height) / 2, 0, static_cast<float>(height) / 2,
					0, 0, static_cast<float>(d) / 2, static_cast<float>(d) / 2,
					0, 0, 0, 1 };
}

Matrix Rasteriser::Translate(float translateX, float translateY, float translateZ)
{
	return { 1, 0, 0, translateX,
			0, 1, 0, translateY,
			0, 0, 1, translateZ,
			0, 0, 0, 1 };
}

Matrix Rasteriser::Scale(float scaleX, float scaleY, float scaleZ)
{
	return { scaleX, 0, 0, 0,
			0, scaleY, 0, 0,
			0, 0, scaleZ, 0,
			0, 0, 0, 1 };
}

Matrix Rasteriser::RotateX(float radians)
{
	return { 1, 0, 0, 0,
			0, static_cast<float>(cos(radians)), static_cast<float>(-sin(radians)), 0,
			0, static_cast<float>(sin(radians)), static_cast<float>(cos(radians)), 0,
			0, 0, 0, 1 };
}

Matrix Rasteriser::RotateY(float radians)
{
	return { static_cast<float>(cos(radians)), 0, static_cast<float>(sin(radians)), 0,
			0, 1, 0, 0,
			static_cast<float>(-sin(radians)), 0, static_cast<float>(cos(radians)), 0,
			0, 0, 0, 1 };
}

Matrix Rasteriser::RotateZ(float radians)
{
	return { static_cast<float>(cos(radians)), static_cast<float>(-sin(radians)), 0, 0,
			static_cast<float>(sin(radians)), static_cast<float>(cos(radians)), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1 };
}

Matrix Rasteriser::TransformCombined(float angleX, float angleY, float angleZ, float scaleX, float scaleY, float scaleZ, float translateX, float translateY, float translateZ)
{
	return RotateX(angleX) * RotateY(angleY) * RotateZ(angleZ) * Scale(scaleX, scaleY, scaleZ) * Translate(translateX, translateY, translateZ);
}

vector<DirectionalLighting> Rasteriser::GetDirectionalLights()
{
	return _directionalLights;
}

void Rasteriser::AddDirectionalLights(DirectionalLighting light_source)
{
	_directionalLights.push_back(light_source);
}

void Rasteriser::AddAmbientLights(AmbientLighting light_source)
{
	_ambientLights.push_back(light_source);
}

vector<AmbientLighting> Rasteriser::GetAmbientLights()
{
	return _ambientLights;
}

void Rasteriser::AddPointLights(PointLighting light_source)
{
	_pointLights.push_back(light_source);
}

vector<PointLighting> Rasteriser::GetPointLights()
{
	return _pointLights;
}

void Rasteriser::DrawString(const Bitmap& bitmap, LPCTSTR text)
{
	HDC hdc = bitmap.GetDC();
	HFONT hFont, hOldFont;

	// Retrieve a handle to the variable stock font.  
	hFont = hFont = CreateFont(48, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Myfont"));

	// Select the variable stock font into the specified device context. 
	if (hOldFont = (HFONT)SelectObject(hdc, hFont))
	{
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(100, 100, 100));

		// Display the text string.  
		TextOut(hdc, 10, 10, text, lstrlen(text));

		// Restore the original font.        
		SelectObject(hdc, hOldFont);
	}
	DeleteObject(hFont);
}