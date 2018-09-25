#pragma once

#include <DirectXMath.h>

// --------------------------------------------------------
// A custom vertex definition
// --------------------------------------------------------
struct Vertex
{
	DirectX::XMFLOAT3 Position;	// The position of the vertex
	DirectX::XMFLOAT3 Normal;	// The Normal of the vertex
	DirectX::XMFLOAT2 uv;		// UV of the vertex
};