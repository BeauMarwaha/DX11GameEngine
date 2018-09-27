#pragma once

#include <DirectXMath.h>

// --------------------------------------------------------
// A struct defining the properties of a directional light
// --------------------------------------------------------
struct DirectionalLight
{
	DirectX::XMFLOAT4 AmbientColor;	// The ambient color of the light
	DirectX::XMFLOAT4 DiffuseColor;	// The diffuse color of the light
	DirectX::XMFLOAT3 Direction;	// The direction the light is pointing
};