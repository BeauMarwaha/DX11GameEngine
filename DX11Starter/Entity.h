#pragma once

#include <DirectXMath.h>
#include "Mesh.h"

// --------------------------------------------------------
// A Entity class that represents a singular game object
// --------------------------------------------------------
class Entity
{
public:
	Entity(Mesh* mesh); // Constructor
	Entity(Entity const& other); // Copy Constructor
	Entity& operator=(Entity const& other); // Copy Assignment Operator
	~Entity(); // Destructor

	// Updates the game object
	void Update();

	// GET methods
	DirectX::XMFLOAT4X4 GetWorldMatrix();
	DirectX::XMFLOAT3 GetPosition();
	DirectX::XMFLOAT3 GetRotation();
	DirectX::XMFLOAT3 GetScale();
	Mesh* GetMesh();

	// SET methods
	void SetWorldMatrix(DirectX::XMFLOAT4X4 worldMatrix);
	void SetPosition(DirectX::XMFLOAT3 position);
	void SetRotation(DirectX::XMFLOAT3 rotation);
	void SetScale(DirectX::XMFLOAT3 scale);
	void SetMesh(Mesh* mesh);

	// Helper methods
	DirectX::XMFLOAT4X4 GetIdentityMatrix();
private:
	// World Matrix representing the entity’s current position, rotation, and scale
	DirectX::XMFLOAT4X4 worldMatrix;

	// Position, Rotation, Scale Vectors
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 scale;

	// Entity Mesh
	Mesh* mesh;
};

