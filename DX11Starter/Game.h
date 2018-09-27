#pragma once

#include "DXCore.h"
#include "SimpleShader.h"
#include "Entity.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include <DirectXMath.h>
#include <vector>

class Game 
	: public DXCore
{

public:
	Game(HINSTANCE hInstance);
	~Game();

	// Overridden setup and game loop methods, which
	// will be called automatically
	void Init();
	void OnResize();
	void Update(float deltaTime, float totalTime);
	void Draw(float deltaTime, float totalTime);

	// Overridden mouse input helper methods
	void OnMouseDown (WPARAM buttonState, int x, int y);
	void OnMouseUp	 (WPARAM buttonState, int x, int y);
	void OnMouseMove (WPARAM buttonState, int x, int y);
	void OnMouseWheel(float wheelDelta,   int x, int y);

private:
	// Initialization helper methods - feel free to customize, combine, etc.
	void LoadShaders(); 
	void CreateBasicGeometry();
	void LoadModels();

	// Entity Vector Collection
	std::vector<Entity> entities;

	// Mesh Pointer Vector Collection
	std::vector<Mesh*> meshes;

	// FPS camera
	Camera* camera;

	// Wrappers for DirectX shaders to provide simplified functionality
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;

	// Basic Material reference
	Material* material;

	// Keeps track of the old mouse position.  Useful for 
	// determining how far the mouse moved in a single frame.
	POINT prevMousePos;

	// Indicates whether the left mouse button is pressed
	bool mouseDown;

	// Enviromental Directional Light
	DirectionalLight light;
};

