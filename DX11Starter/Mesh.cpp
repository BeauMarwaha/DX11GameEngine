#include "Mesh.h"

Mesh::Mesh(ID3D11Device* device, Vertex* vertices, int vertexCount, unsigned int* indices, int indexCount)
{
	// Create the VERTEX BUFFER description -----------------------------------
	// - The description is created on the stack because we only need
	//    it to create the buffer.  The description is then useless.
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * vertexCount; 
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER; // Tells DirectX this is a vertex buffer
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	// Create the proper struct to hold the initial vertex data
	// - This is how we put the initial data into the buffer
	D3D11_SUBRESOURCE_DATA initialVertexData;
	initialVertexData.pSysMem = vertices;

	// Actually create the buffer with the initial data
	// - Once we do this, we'll NEVER CHANGE THE BUFFER AGAIN
	device->CreateBuffer(&vbd, &initialVertexData, &vertexBuffer);


	// Create the INDEX BUFFER description ------------------------------------
	// - The description is created on the stack because we only need
	//    it to create the buffer.  The description is then useless.
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(unsigned int) * indexCount;   
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER; // Tells DirectX this is an index buffer
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	// Create the proper struct to hold the initial index data
	// - This is how we put the initial data into the buffer
	D3D11_SUBRESOURCE_DATA initialIndexData;
	initialIndexData.pSysMem = indices;

	// Actually create the buffer with the initial data
	// - Once we do this, we'll NEVER CHANGE THE BUFFER AGAIN
	device->CreateBuffer(&ibd, &initialIndexData, &indexBuffer);

	// Copy the passed in number of indices to the member count variable 
	this->indexCount = indexCount;
}

Mesh::Mesh(Mesh const& other)
{
	vertexBuffer = other.vertexBuffer;
	vertexBuffer->AddRef(); // Tell DirectX there is a new reference to this object
	indexBuffer = other.indexBuffer;
	indexBuffer->AddRef(); // Tell DirectX there is a new reference to this object
	indexCount = other.indexCount;
}

Mesh & Mesh::operator=(Mesh const& other)
{
	if (this != &other)
	{
		// Switch values
		vertexBuffer = other.vertexBuffer;
		vertexBuffer->AddRef(); // Tell DirectX there is a new reference to this object
		indexBuffer = other.indexBuffer;
		indexBuffer->AddRef(); // Tell DirectX there is a new reference to this object
		indexCount = other.indexCount;
	}
	return *this;
}

Mesh::~Mesh()
{
	// Release the vertex and index buffers
	if (vertexBuffer) { vertexBuffer->Release(); }
	if (indexBuffer) { indexBuffer->Release(); }
}

ID3D11Buffer* Mesh::GetVertexBuffer()
{
	vertexBuffer->AddRef(); // Tell DirectX there is a new reference to this object
	return vertexBuffer;
}

ID3D11Buffer* Mesh::GetIndexBuffer()
{
	indexBuffer->AddRef(); // Tell DirectX there is a new reference to this object
	return indexBuffer;
}

int Mesh::GetIndexCount()
{
	return indexCount;
}
