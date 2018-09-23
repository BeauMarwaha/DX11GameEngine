#pragma once

#include <DirectXMath.h>
#include "SimpleShader.h"

class Material
{
public:
	Material(SimpleVertexShader* vertexShader, SimplePixelShader* pixelShader); // Constructor
	~Material(); // Destructor

	// GET methods
	SimpleVertexShader* GetVertexShader();
	SimplePixelShader* GetPixelShader();

private:
	// Wrappers for DirectX shaders to provide simplified functionality
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;
};

