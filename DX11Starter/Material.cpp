#include "Material.h"

// For the DirectX Math library
using namespace DirectX;

Material::Material(SimpleVertexShader* vertexShader, SimplePixelShader* pixelShader)
{
	this->vertexShader = vertexShader;
	this->pixelShader = pixelShader;
}

Material::~Material()
{
}

SimpleVertexShader * Material::GetVertexShader()
{
	return vertexShader;
}

SimplePixelShader * Material::GetPixelShader()
{
	return pixelShader;
}
