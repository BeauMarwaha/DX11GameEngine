#include "Entity.h"

// For the DirectX Math library
using namespace DirectX;

Entity::Entity(Mesh* mesh)
{
	// Use the passed in mesh
	this->mesh = mesh;

	// Set the location vectors and matrix to default values
	position = XMFLOAT3(0, 0, 0);
	rotation = XMFLOAT3(0, 0, 0);
	scale = XMFLOAT3(1, 1, 1);
	worldMatrix = GetIdentityMatrix();
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

void Entity::Update(float deltaTime, float totalTime)
{
	// Update the world matrix based on the position, rotation, and scale
	XMStoreFloat4x4(&worldMatrix,
		XMMatrixTranslation(position.x, position.y, position.z) *
		XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z) *
		XMMatrixScaling(scale.x, scale.y, scale.z));
}

XMFLOAT4X4 Entity::GetWorldMatrix()
{
	return worldMatrix;
}

XMFLOAT3 Entity::GetPosition()
{
	return position;
}

XMFLOAT3 Entity::GetRotation()
{
	return rotation;
}

XMFLOAT3 Entity::GetScale()
{
	return scale;
}

Mesh* Entity::GetMesh()
{
	return mesh;
}

void Entity::SetWorldMatrix(XMFLOAT4X4 worldMatrix)
{
	this->worldMatrix = worldMatrix;
}

void Entity::SetPosition(XMFLOAT3 position)
{
	this->position = position;
}

void Entity::SetRotation(XMFLOAT3 rotation)
{
	this->rotation = rotation;
}

void Entity::SetScale(XMFLOAT3 scale)
{
	this->scale = scale;
}

void Entity::SetMesh(Mesh* mesh)
{
	this->mesh = mesh;
}

void Entity::Move(XMFLOAT3 direction, XMFLOAT3 velocity)
{
	XMVECTOR initialPos = XMLoadFloat3(&position);
	XMVECTOR movement = XMVector3Rotate(XMLoadFloat3(&velocity), XMQuaternionRotationRollPitchYawFromVector(XMLoadFloat3(&direction)));
	XMStoreFloat3(&position, initialPos + movement);
}

void Entity::MoveForward(XMFLOAT3 velocity)
{
	XMVECTOR initialPos = XMLoadFloat3(&position);
	XMVECTOR movement = XMVector3Rotate(XMLoadFloat3(&velocity), XMQuaternionRotationRollPitchYawFromVector(XMLoadFloat3(&rotation)));
	XMStoreFloat3(&position, initialPos + movement);
}

XMFLOAT4X4 Entity::GetIdentityMatrix()
{
	XMFLOAT4X4 identityMatrix = XMFLOAT4X4();
	XMStoreFloat4x4(&identityMatrix, XMMatrixIdentity());
	return identityMatrix;
}
