#include "Entity.h"

Entity::Entity(Mesh* mesh)
{
	// Use the passed in mesh
	this->mesh = mesh;

	// Set the location vectors and matrix to default values
	position = DirectX::XMFLOAT3(0, 0, 0);
	rotation = DirectX::XMFLOAT3(0, 0, 0);
	scale = DirectX::XMFLOAT3(1, 1, 1);
	worldMatrix = DirectX::XMFLOAT4X4();
}

Entity::Entity(Entity const & other)
{
	mesh = other.mesh;
	position = other.position;
	rotation = other.rotation;
	scale = other.scale;
	worldMatrix = other.worldMatrix;
}

Entity & Entity::operator=(Entity const & other)
{
	if (this != &other)
	{
		// Switch values
		mesh = other.mesh;
		position = other.position;
		rotation = other.rotation;
		scale = other.scale;
		worldMatrix = other.worldMatrix;
	}
	return *this;
}

Entity::~Entity()
{
}

void Entity::Update()
{
	// Update the world matrix based on the position, rotation, and scale
	//worldMatrix = position * rotation * scale;
}

DirectX::XMFLOAT4X4 Entity::GetWorldMatrix()
{
	return worldMatrix;
}

DirectX::XMFLOAT3 Entity::GetPosition()
{
	return position;
}

DirectX::XMFLOAT3 Entity::GetRotation()
{
	return rotation;
}

DirectX::XMFLOAT3 Entity::GetScale()
{
	return scale;
}

Mesh* Entity::GetMesh()
{
	return mesh;
}

void Entity::SetWorldMatrix(DirectX::XMFLOAT4X4 worldMatrix)
{
	this->worldMatrix = worldMatrix;
}

void Entity::SetPosition(DirectX::XMFLOAT3 position)
{
	this->position = position;
}

void Entity::SetRotation(DirectX::XMFLOAT3 rotation)
{
	this->rotation = rotation;
}

void Entity::SetScale(DirectX::XMFLOAT3 scale)
{
	this->scale = scale;
}

void Entity::SetMesh(Mesh* mesh)
{
	this->mesh = mesh;
}
