#pragma once

#include <d3d11.h>
#include "Vertex.h"

// --------------------------------------------------------
// A Mesh class that can take vertex and index data for a 
//  model and create/store the requisite related buffers 
//  and mesh-related data for later use
// --------------------------------------------------------
class Mesh
{
public:
	Mesh(ID3D11Device* device, Vertex* vertexes, int vertexCount, unsigned int* indices, int indexCount); // Constructor
	Mesh(Mesh const& other); // Copy Constructor
	Mesh& operator=(Mesh const& other); // Copy Assignment Operator
	~Mesh(); // Destructor

	// GET methods
	ID3D11Buffer* GetVertexBuffer();
	ID3D11Buffer* GetIndexBuffer();
	int GetIndexCount();

private:
	// Buffers to hold actual geometry data
	ID3D11Buffer* vertexBuffer = nullptr;
	ID3D11Buffer* indexBuffer = nullptr;

	// Integer specifying how many indices are in the mesh's index buffer
	int indexCount = 0;
};

