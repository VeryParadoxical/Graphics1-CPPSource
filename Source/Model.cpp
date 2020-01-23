#include "Model.h"
#include <algorithm>

/* _100477500 Graphics I */

Model::Model() 
{
}

Model::~Model() 
{
};

const std::vector<Polygon3D>& Model::GetPolygons() 
{
	return _polygons;
}

const std::vector<Vertex>& Model::GetVertices()
{
	return _vertices;
}

const std::vector<Vertex>& Model::GetTransformedVertices()
{
	return _transformedVertices;
}

size_t Model::GetPolygonCount() const
{
	return _polygons.size();
}

size_t Model::GetBaseVertexCount() const
{
	return _vertices.size();
}

size_t Model::GetTransformedVertexCount() const
{
	return _transformedVertices.size();
}

void Model::DehomogeniseModel()
{
	for (size_t i = 0; i < GetTransformedVertexCount(); i++)
	{
		_transformedVertices[i].Dehomogenise();
	}
}

void Model::AddVertex(float x, float y, float z)
{
	_vertices.push_back(Vertex(x, y, z));
};

void Model::AddPolygon(int i0, int i1, int i2)
{
	_polygons.push_back(Polygon3D(i0, i1, i2));
};

void Model::ApplyTransformToLocalVertices(const Matrix& transformation)
{
	_transformedVertices.clear();
	for (size_t i =0; i < GetBaseVertexCount(); i++)
	{
		_transformedVertices.push_back(transformation * _vertices[i]);
	}
};

void Model::ApplyTransformToTransformedVertices(const Matrix& transformation)
{
	for (Vertex& vertex : _transformedVertices)
	{
		vertex = transformation * vertex;
	}
};

void Model::BackfaceCulling(const Vertex& cameraPosition)
{
	for (size_t i = 0; i < GetPolygonCount(); i++)
	{
		Vertex vertex0 = _transformedVertices[_polygons[i].GetIndex(0)];
		Vertex vertex1 = _transformedVertices[_polygons[i].GetIndex(1)];
		Vertex vertex2 = _transformedVertices[_polygons[i].GetIndex(2)];

		Vector3D vector_a = vertex0.CreateVector(vertex2);//construct vector a by subtracting vertex 1 from vertex 0 
		Vector3D vector_b = vertex0.CreateVector(vertex1);//construct vector b by subtracting vertex 2 from vertex 0 
		Vector3D normal = Vector3D::CrossProduct(vector_b, vector_a);

		_polygons[i].SetNormal(Vector3D::CrossProduct(vector_b, vector_a)); //calculate the normal vector from b and a and save it in the polygon
		
		Vector3D eye_vector = (cameraPosition.CreateVector(vertex0));	//create eye-vector = vertex 0 - camera position
		float dotResult = Vector3D::DotProduct(_polygons[i].GetNormal(), eye_vector);   //take dot result of the normal and the eye vector

		if (dotResult > 0)
		{
			_polygons[i].SetVisibility(false);
		}
		else
		{
			_polygons[i].SetVisibility(true);
		}
	}
}

void Model::Sort()
{
	for (size_t i = 0; i < GetPolygonCount(); i++)
	{
		Vertex vertex0 = _transformedVertices[_polygons[i].GetIndex(0)];
		Vertex vertex1 = _transformedVertices[_polygons[i].GetIndex(1)];
		Vertex vertex2 = _transformedVertices[_polygons[i].GetIndex(2)];

		_polygons[i].SetAverageZ((vertex0.GetZ() + vertex1.GetZ() + vertex2.GetZ()) / 3.0f);
	}
	sort(_polygons.begin(), _polygons.end(), [](Polygon3D & i, Polygon3D & i2)
		{
			return i.GetAverageZ() > i2.GetAverageZ();
		}
	);
}

float Model::GetKA_Red()
{
	return _ka_red;
}

float Model::GetKA_Green()
{
	return _ka_green;
}

float Model::GetKA_Blue()
{
	return _ka_blue;
}

float Model::GetKD_Red()
{
	return _kd_red;
}

float Model::GetKD_Blue()
{
	return _kd_blue;
}

float Model::GetKD_Green()
{
	return _kd_green;
}

float Model::GetKS_Red()
{
	return _ks_red;
}

float Model::GetKS_Blue()
{
	return _ks_blue;
}


float Model::GetKS_Green()
{
	return _ks_green;
}

void Model::CalculateLightingDirectional(std::vector<DirectionalLighting> directional_lights)
{
	int total_r = 0;
	int total_g = 0;
	int total_b = 0;
	int temp_r = 0;
	int temp_g = 0;
	int temp_b = 0;

	for (size_t i = 0; i < GetPolygonCount(); i++)
	{
		_total = _polygons[i].GetColour();
		total_r = GetRValue(_total);
		total_g = GetGValue(_total);
		total_b = GetBValue(_total);

		for (DirectionalLighting light_source : directional_lights)
		{
			float _dotResult = Vector3D::DotProduct(Vector3D::Normalise(light_source.GetLightDirection()), Vector3D::Normalise(_polygons[i].GetNormal()));
			if (_dotResult > 0)
			{
				COLORREF intensity = light_source.GetLightIntensity();
				temp_r = GetRValue(intensity);
				temp_g = GetGValue(intensity);
				temp_b = GetBValue(intensity);
				/*To ensure the reflectance coefficients do not lose their function/accuracy (rounding from 0.7 to 1)
				when being multiplied by an int temp rgb value they are cased to a float for calculations. */
				float _fl_temp_r = static_cast<float>(temp_r);
				float _fl_temp_g = static_cast<float>(temp_g);
				float _fl_temp_b = static_cast<float>(temp_b);

				total_r += static_cast<int>(_fl_temp_r * GetKD_Red() * _dotResult);
				total_g += static_cast<int>(_fl_temp_g * GetKD_Green() * _dotResult);
				total_b += static_cast<int>(_fl_temp_b * GetKD_Blue() * _dotResult);
			}
		}
		_total = (RGB(RGBClamping(total_r), RGBClamping(total_g), RGBClamping(total_b)));
		_polygons[i].SetColour(_total);
	}
}


void Model::CalculateLightingAmbient(std::vector<AmbientLighting> ambient_lights)
{
	for (size_t i = 0; i < GetPolygonCount(); i++)
	{
		for (AmbientLighting light_source : ambient_lights)
		{
			_temp = light_source.GetLightIntensity();
			float temp_r = (static_cast<float>(GetRValue(_temp))) * GetKA_Red();
			float temp_g = (static_cast<float>(GetGValue(_temp))) * GetKA_Green();
			float temp_b = (static_cast<float>(GetBValue(_temp))) * GetKA_Blue();

			COLORREF colour = COLORREF(RGB(static_cast<int>(temp_r), static_cast<int>(temp_g), static_cast<int>(temp_b)));

			int index0 = _polygons[i].GetIndex(0);
			int index1 = _polygons[i].GetIndex(1);
			int index2 = _polygons[i].GetIndex(2);

			_transformedVertices[index0].SetColour(colour);
			_transformedVertices[index1].SetColour(colour);
			_transformedVertices[index2].SetColour(colour);

			_polygons[i].SetColour(colour);
		}

	}
}


void Model::CalculateLightingPoint(std::vector<PointLighting> point_lights)
{
	int total_r;
	int total_g;
	int total_b;
	int temp_r;
	int temp_g;
	int temp_b;

	for (size_t i = 0; i < GetPolygonCount(); i++)
	{
		_total = _polygons[i].GetColour();
		total_r = GetRValue(_total);
		total_g = GetGValue(_total);
		total_b = GetBValue(_total);

		for (PointLighting light_source : point_lights)
		{

			Vertex light_position = light_source.GetLightPosition();
			Vertex vertex0 = _transformedVertices[_polygons[i].GetIndex(0)];
			Vector3D vector_to_source = Vector3D(vertex0.GetX() - light_position.GetX(), vertex0.GetY() - light_position.GetY(), vertex0.GetZ() - light_position.GetZ());

			float _dotResult = Vector3D::DotProduct(Vector3D::Normalise(vector_to_source), Vector3D::Normalise(_polygons[i].GetNormal()));

			if (_dotResult > 0)
			{
				COLORREF intensity = light_source.GetLightIntensity();
				temp_r = GetRValue(intensity);
				temp_g = GetGValue(intensity);
				temp_b = GetBValue(intensity);

				float _fl_temp_r = static_cast<float>(temp_r);
				float _fl_temp_g = static_cast<float>(temp_g);
				float _fl_temp_b = static_cast<float>(temp_b);

				_fl_temp_r *= GetKD_Red();
				_fl_temp_g *= GetKD_Green();
				_fl_temp_b *= GetKD_Blue();

				_fl_temp_r *= _dotResult;
				_fl_temp_g *= _dotResult;
				_fl_temp_b *= _dotResult;

				float vector_length = vector_to_source.GetLength();
				float attenuation = 100.0f / (light_source.GetAttenuationA() + light_source.GetAttenuationB() * vector_length + light_source.GetAttenuationC() * vector_length * vector_length);

				_fl_temp_r *= attenuation;
				_fl_temp_g *= attenuation;
				_fl_temp_b *= attenuation;

				total_r += static_cast<int>(_fl_temp_r);
				total_g += static_cast<int>(_fl_temp_g);
				total_b += static_cast<int>(_fl_temp_b);
			}
		}
		_total += (RGB(RGBClamping(total_r), RGBClamping(total_g), RGBClamping(total_b)));
		_polygons[i].SetColour(_total);
	}
}

int Model::RGBClamping(int rgbval) 
{
	if (rgbval > 255) 
	{
		return 255;
	}
	else if (rgbval < 0) 
	{
		return 0;
	}
	else 
	{
		return rgbval;
	}
}

void Model::CalculateVertexNormals()
{
	//for (size_t i = 0; i < GetTransformedVertexCount(); i++)
	for (Vertex& v : _transformedVertices)
	{
		v.SetContributeCount(0); //_transformedVertices[i]
		v.SetNormal(Vector3D( 0,0,0 )); //_transformedVertices[i]

	}
	for (Polygon3D& p : _polygons)
	{
		Vertex v0 = _transformedVertices[p.GetIndex(0)];
		Vertex v1 = _transformedVertices[p.GetIndex(1)];
		Vertex v2 = _transformedVertices[p.GetIndex(2)];
		v0.SetNormal(v0.GetNormal() + p.GetNormal());
		v1.SetNormal(v1.GetNormal() + p.GetNormal());
		v2.SetNormal(v2.GetNormal() + p.GetNormal());
		v0.ContributeCountIncrement();
		v1.ContributeCountIncrement();
		v2.ContributeCountIncrement();
	}

	for (Vertex& v : _transformedVertices)
	{
		Vector3D normal = v.GetNormal();
		int count = v.GetContributeCount();
		v.SetNormal(Vector3D::Normalise(Vector3D((normal.GetX() / count), (normal.GetY() / count), (normal.GetZ() / count))));
	}
}


void Model::CalculateLightingDirectionalVertices(std::vector<DirectionalLighting> directional_lights)
{
	int total_r = 0;
	int total_g = 0;
	int total_b = 0;
	int temp_r = 0;
	int temp_g = 0;
	int temp_b = 0;


	for (Vertex& v : _transformedVertices)
	{
		_total = v.GetColour(); 

		total_r = GetRValue(_total);
		total_g = GetGValue(_total);
		total_b = GetBValue(_total);

		for (DirectionalLighting light_source : directional_lights)
		{
			float _dotResult = Vector3D::DotProduct(Vector3D::Normalise(light_source.GetLightDirection()), Vector3D::Normalise(v.GetNormal()));  

			if (_dotResult > 0)
			{
				COLORREF intensity = light_source.GetLightIntensity();
				temp_r = GetRValue(intensity);
				temp_g = GetGValue(intensity);
				temp_b = GetBValue(intensity);
				/*To ensure the reflectance coefficients do not lose their function/accuracy (rounding from 0.7 to 1)
				when being multiplied by an int temp rgb value they are cased to a float for calculations. */
				float _fl_temp_r = static_cast<float>(temp_r);
				float _fl_temp_g = static_cast<float>(temp_g);
				float _fl_temp_b = static_cast<float>(temp_b);

				total_r += static_cast<int>(_fl_temp_r * GetKD_Red() * _dotResult);
				total_g += static_cast<int>(_fl_temp_g * GetKD_Green() * _dotResult);
				total_b += static_cast<int>(_fl_temp_b * GetKD_Blue() * _dotResult);
			}
		}
		_total = COLORREF(RGB(RGBClamping(GetRValue(_total) + (total_r)), RGBClamping(GetGValue(_total) + (total_g)), RGBClamping(GetBValue(_total) + (total_b))));
		//_total += COLORREF(RGB(RGBClamping(total_r), RGBClamping(total_g), RGBClamping(total_b)));
		v.SetColour(_total); 
	}
}

void Model::CalculateLightingPointVertices(std::vector<PointLighting> point_lights)
{
	int total_r;
	int total_g;
	int total_b;
	int temp_r;
	int temp_g;
	int temp_b;

	//for (size_t i = 0; i < GetTransformedVertexCount(); i++)
	for (Vertex& p : _transformedVertices)
	{
		_total = p.GetColour();
		total_r = GetRValue(_total);
		total_g = GetGValue(_total);
		total_b = GetBValue(_total);

		for (PointLighting light_source : point_lights)
		{
			Vertex light_position = light_source.GetLightPosition();
			Vector3D vector_to_source = Vector3D(p.GetX() - light_position.GetX(), p.GetY() - light_position.GetY(), p.GetZ() - light_position.GetZ());

			float _dotResult = Vector3D::DotProduct(Vector3D::Normalise(vector_to_source), Vector3D::Normalise(p.GetNormal()));

			if (_dotResult > 0)
			{
				COLORREF intensity = light_source.GetLightIntensity();
				temp_r = GetRValue(intensity);
				temp_g = GetGValue(intensity);
				temp_b = GetBValue(intensity);

				float _fl_temp_r = static_cast<float>(temp_r);
				float _fl_temp_g = static_cast<float>(temp_g);
				float _fl_temp_b = static_cast<float>(temp_b);

				_fl_temp_r *= GetKD_Red();
				_fl_temp_g *= GetKD_Green();
				_fl_temp_b *= GetKD_Blue();

				_fl_temp_r *= _dotResult;
				_fl_temp_g *= _dotResult;
				_fl_temp_b *= _dotResult;

				float vector_length = vector_to_source.GetLength();
				float attenuation = 100.0f / (light_source.GetAttenuationA() + light_source.GetAttenuationB() * vector_length + light_source.GetAttenuationC() * vector_length * vector_length);

				_fl_temp_r *= attenuation;
				_fl_temp_g *= attenuation;
				_fl_temp_b *= attenuation;

				total_r += static_cast<int>(_fl_temp_r);
				total_g += static_cast<int>(_fl_temp_g);
				total_b += static_cast<int>(_fl_temp_b);
			}
		}
		_total += (RGB(RGBClamping(total_r), RGBClamping(total_g), RGBClamping(total_b)));
		p.SetColour(_total);
	}
}
