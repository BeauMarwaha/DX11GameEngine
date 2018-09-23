#include "Game.h"
#include "Vertex.h"

// For the DirectX Math library
using namespace DirectX;

// --------------------------------------------------------
// Constructor
//
// DXCore (base class) constructor will set up underlying fields.
// DirectX itself, and our window, are not ready yet!
//
// hInstance - the application's OS-level handle (unique ID)
// --------------------------------------------------------
Game::Game(HINSTANCE hInstance)
	: DXCore(
		hInstance,		   // The application's handle
		"DirectX Game",	   // Text for the window's title bar
		1280,			   // Width of the window's client area
		720,			   // Height of the window's client area
		true)			   // Show extra stats (fps) in title bar?
{
	// Initialize fields
	mouseDown = false;
	meshes = std::vector<Mesh*>();
	entities = std::vector<Entity>();
	camera = new Camera(width, height);
	vertexShader = 0;
	pixelShader = 0;

#if defined(DEBUG) || defined(_DEBUG)
	// Do we want a console window?  Probably only in debug mode
	CreateConsoleWindow(500, 120, 32, 120);
	printf("Console window created successfully.  Feel free to printf() here.");
#endif
	
}

// --------------------------------------------------------
// Destructor - Clean up anything our game has created:
//  - Release all DirectX objects created here
//  - Delete any objects to prevent memory leaks
// --------------------------------------------------------
Game::~Game()
{
	// Delete the camera
	delete camera;

	// Delete our simple shader objects, which
	// will clean up their own internal DirectX stuff
	delete vertexShader;
	delete pixelShader;

	// Delete all entrys in the Mesh Pointer Vector Collection
	for (std::vector<Mesh>::size_type i = 0; i != meshes.size(); i++) {
		delete meshes[i];
	}
}

// --------------------------------------------------------
// Called once per program, after DirectX and the window
// are initialized but before the game loop.
// --------------------------------------------------------
void Game::Init()
{
	// Helper methods for loading shaders, creating some basic
	// geometry to draw and some simple camera matrices.
	//  - You'll be expanding and/or replacing these later
	LoadShaders();
	CreateBasicGeometry();

	// Tell the input assembler stage of the pipeline what kind of
	// geometric primitives (points, lines or triangles) we want to draw.  
	// Essentially: "What kind of shape should the GPU draw with our data?"
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

// --------------------------------------------------------
// Loads shaders from compiled shader object (.cso) files using
// my SimpleShader wrapper for DirectX shader manipulation.
// - SimpleShader provides helpful methods for sending
//   data to individual variables on the GPU
// --------------------------------------------------------
void Game::LoadShaders()
{
	vertexShader = new SimpleVertexShader(device, context);
	vertexShader->LoadShaderFile(L"VertexShader.cso");

	pixelShader = new SimplePixelShader(device, context);
	pixelShader->LoadShaderFile(L"PixelShader.cso");
}

// --------------------------------------------------------
// Creates the geometry we're going to draw 
// - For now this will be three simple Mesh objects
// --------------------------------------------------------
void Game::CreateBasicGeometry()
{
	// Create some temporary variables to represent colors
	// - Not necessary, just makes things more readable
	XMFLOAT4 red = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 green = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	XMFLOAT4 blue = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);

	// Set up the vertices and indices for Mesh 1 ---------------------------------
	// Set up the vertices of the triangle we would like to draw
	// - We're going to copy this array, exactly as it exists in memory
	//    over to a DirectX-controlled data structure (the vertex buffer)
	Vertex vertices1[] =
	{
		{ XMFLOAT3(+0.0f, +1.0f, +0.0f), red },
		{ XMFLOAT3(+1.5f, -1.0f, +0.0f), blue },
		{ XMFLOAT3(-1.5f, -1.0f, +0.0f), green }
	};

	// Set up the indices, which tell us which vertices to use and in which order
	// - This is somewhat redundant for just 3 vertices (it's a simple example)
	// - Indices are technically not required if the vertices are in the buffer 
	//    in the correct order and each one will be used exactly once
	unsigned int indices1[] = { 0, 1, 2 };

	// Calculate the number of vertices and indicies
	int vertexCount1 = sizeof(vertices1) / sizeof(vertices1[0]);
	int indexCount1 = sizeof(indices1) / sizeof(indices1[0]);

	// Create the actual Mesh object for Mesh 1
	meshes.push_back(new Mesh(device, vertices1, vertexCount1, indices1, indexCount1));
	
	// Set up the vertices and indices for Mesh 2 ---------------------------------
	Vertex vertices2[] =
	{
		{ XMFLOAT3(+2.0f, +1.0f, +0.0f), red },
		{ XMFLOAT3(+3.5f, -1.0f, +0.0f), green },
		{ XMFLOAT3(+2.0f, -1.0f, +0.0f), blue },
		{ XMFLOAT3(+3.5f, +1.0f, +0.0f), green }
	};
	unsigned int indices2[] = { 0, 1, 2, 0, 3, 1 };

	// Calculate the number of vertices and indicies
	int vertexCount2 = sizeof(vertices2) / sizeof(vertices2[0]);
	int indexCount2 = sizeof(indices2) / sizeof(indices2[0]);

	// Create the actual Mesh object for Mesh 1
	meshes.push_back(new Mesh(device, vertices2, vertexCount2, indices2, indexCount2));

	// Set up the vertices and indices for Mesh 3 ---------------------------------
	Vertex vertices3[] =
	{
		{ XMFLOAT3(-2.0f, +1.0f, +0.0f), blue },
		{ XMFLOAT3(-2.0f, -1.0f, +0.0f), red },
		{ XMFLOAT3(-3.5f, -1.0f, +0.0f), green },
		{ XMFLOAT3(-3.5f, +1.0f, +0.0f), green }
	};
	unsigned int indices3[] = { 0, 1, 2, 3, 0, 2 };

	// Calculate the number of vertices and indicies
	int vertexCount3 = sizeof(vertices3) / sizeof(vertices3[0]);
	int indexCount3 = sizeof(indices3) / sizeof(indices3[0]);

	// Create the actual Mesh object for Mesh 1
	meshes.push_back(new Mesh(device, vertices3, vertexCount3, indices3, indexCount3));

	// Assign created meshes to new entities
	entities.push_back(Entity(meshes[0]));
	entities.push_back(Entity(meshes[0]));
	entities.push_back(Entity(meshes[1]));
	entities.push_back(Entity(meshes[2]));
	entities.push_back(Entity(meshes[1]));
	entities.push_back(Entity(meshes[2]));
}


// --------------------------------------------------------
// Handle resizing DirectX "stuff" to match the new window size.
// For instance, updating our projection matrix's aspect ratio.
// --------------------------------------------------------
void Game::OnResize()
{
	// Handle base-level DX resize stuff
	DXCore::OnResize();

	// Update our camera's projection matrix since the window size changed
	camera->ResizeWindow(width, height);
}

// --------------------------------------------------------
// Update your game here - user input, move objects, AI, etc.
// --------------------------------------------------------
void Game::Update(float deltaTime, float totalTime)
{
	// Quit if the escape key is pressed
	if (GetAsyncKeyState(VK_ESCAPE))
		Quit();

	// Movement for entity 0
	if (&entities[0] != nullptr)
	{
		// Set movement rate
		float speed = 5.0;

		if (GetAsyncKeyState('I') & 0x8000)
		{
			entities[0].MoveForward(XMFLOAT3(0, speed * deltaTime, 0));
		}

		if (GetAsyncKeyState('K') & 0x8000)
		{
			entities[0].MoveForward(XMFLOAT3(0, -speed * deltaTime, 0));
		}

		if (GetAsyncKeyState('L') & 0x8000)
		{
			entities[0].MoveForward(XMFLOAT3(speed * deltaTime, 0, 0));
		}

		if (GetAsyncKeyState('J') & 0x8000)
		{
			entities[0].MoveForward(XMFLOAT3(-speed * deltaTime, 0, 0));
		}

		if (GetAsyncKeyState('O') & 0x8000)
		{
			entities[0].MoveForward(XMFLOAT3(0, 0, speed * deltaTime));
		}

		if (GetAsyncKeyState('U') & 0x8000)
		{
			entities[0].MoveForward(XMFLOAT3(0, 0, -speed * deltaTime));
		}
	}

	// Rotate entity 1, 4, and 5
	XMFLOAT3 currentRot = entities[1].GetRotation();
	XMFLOAT3 newRot = XMFLOAT3(currentRot.x, currentRot.y, currentRot.z + (1 * deltaTime));
	entities[1].SetRotation(newRot);
	entities[4].SetRotation(newRot);
	entities[5].SetRotation(newRot);

	// Set up the rate of LERP to pulse up and down each second
	float rate = 0.5f;
	if ((long)totalTime % 2 == 0)
	{
		rate = totalTime - (long)totalTime;
	}
	else
	{
		rate = 1 - (totalTime - (long)totalTime);
	}

	// Lerp the scale of entity 2 and 3
	XMFLOAT3 scale = XMFLOAT3(1.0, 1.0, 1.0);
	XMFLOAT3 scaleMin = XMFLOAT3(0.75, 0.75, 0.75);
	XMFLOAT3 scaleMax = XMFLOAT3(1.25, 1.25, 1.25);
	XMStoreFloat3(&scale, XMVectorLerp(XMLoadFloat3(&scaleMin), XMLoadFloat3(&scaleMax), rate));
	entities[2].SetScale(scale);
	entities[3].SetScale(scale);

	// Update the camera
	camera->Update(deltaTime, totalTime);

	// Update all entities
	for (std::vector<Entity>::size_type i = 0; i != entities.size(); i++) 
	{
		entities[i].Update(deltaTime, totalTime);
	}
}

// --------------------------------------------------------
// Clear the screen, redraw everything, present to the user
// --------------------------------------------------------
void Game::Draw(float deltaTime, float totalTime)
{
	// Background color (Cornflower Blue in this case) for clearing
	const float color[4] = { 0.4f, 0.6f, 0.75f, 0.0f };

	// Clear the render target and depth buffer (erases what's on the screen)
	//  - Do this ONCE PER FRAME
	//  - At the beginning of Draw (before drawing *anything*)
	context->ClearRenderTargetView(backBufferRTV, color);
	context->ClearDepthStencilView(
		depthStencilView,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0);

	// Send data to shader variables
	//  - Do this ONCE PER OBJECT you're drawing
	//  - This is actually a complex process of copying data to a local buffer
	//    and then copying that entire buffer to the GPU.  
	//  - The "SimpleShader" class handles all of that for you.
	//vertexShader->SetMatrix4x4("world", worldMatrix);
	vertexShader->SetMatrix4x4("view", camera->GetViewMatrix());
	vertexShader->SetMatrix4x4("projection", camera->GetProjectionMatrix());

	// Once you've set all of the data you care to change for
	// the next draw call, you need to actually send it to the GPU
	//  - If you skip this, the "SetMatrix" calls above won't make it to the GPU!
	vertexShader->CopyAllBufferData();

	// Set the vertex and pixel shaders to use for the next Draw() command
	//  - These don't technically need to be set every frame...YET
	//  - Once you start applying different shaders to different objects,
	//    you'll need to swap the current shaders before each draw
	vertexShader->SetShader();
	pixelShader->SetShader();

	// Set the buffers and draw all meshes for each entity
	for (std::vector<Entity>::size_type i = 0; i != entities.size(); i++) {
		// Set the transposed world matrix in the vertex shader for this entity
		XMFLOAT4X4 worldMatrixTranspose;
		XMStoreFloat4x4(&worldMatrixTranspose, XMMatrixTranspose(XMLoadFloat4x4(&entities[i].GetWorldMatrix())));
		vertexShader->SetMatrix4x4("world", worldMatrixTranspose);
		vertexShader->CopyAllBufferData();

		// Set buffers in the input assembler
		//  - Do this ONCE PER OBJECT you're drawing, since each object might
		//    have different geometry.
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		ID3D11Buffer* vBuffer = entities[i].GetMesh()->GetVertexBuffer();
		context->IASetVertexBuffers(0, 1, &vBuffer, &stride, &offset);
		context->IASetIndexBuffer(entities[i].GetMesh()->GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

		// Finally do the actual drawing
		//  - Do this ONCE PER OBJECT you intend to draw
		//  - This will use all of the currently set DirectX "stuff" (shaders, buffers, etc)
		//  - DrawIndexed() uses the currently set INDEX BUFFER to look up corresponding
		//     vertices in the currently set VERTEX BUFFER
		context->DrawIndexed(
			entities[i].GetMesh()->GetIndexCount(),     // The number of indices to use (we could draw a subset if we wanted)
			0,     // Offset to the first index we want to use
			0);    // Offset to add to each index when looking up vertices
	}

	// Present the back buffer to the user
	//  - Puts the final frame we're drawing into the window so the user can see it
	//  - Do this exactly ONCE PER FRAME (always at the very end of the frame)
	swapChain->Present(0, 0);
}

#pragma region Mouse Input

// --------------------------------------------------------
// Helper method for mouse clicking.  We get this information
// from the OS-level messages anyway, so these helpers have
// been created to provide basic mouse input if you want it.
// --------------------------------------------------------
void Game::OnMouseDown(WPARAM buttonState, int x, int y)
{
	mouseDown = true;

	// Save the previous mouse position, so we have it for the future
	prevMousePos.x = x;
	prevMousePos.y = y;

	// Caputure the mouse so we keep getting mouse move
	// events even if the mouse leaves the window.  we'll be
	// releasing the capture once a mouse button is released
	SetCapture(hWnd);
}

// --------------------------------------------------------
// Helper method for mouse release
// --------------------------------------------------------
void Game::OnMouseUp(WPARAM buttonState, int x, int y)
{
	mouseDown = false;

	// We don't care about the tracking the cursor outside
	// the window anymore (we're not dragging if the mouse is up)
	ReleaseCapture();
}

// --------------------------------------------------------
// Helper method for mouse movement.  We only get this message
// if the mouse is currently over the window, or if we're 
// currently capturing the mouse.
// --------------------------------------------------------
void Game::OnMouseMove(WPARAM buttonState, int x, int y)
{
	// Initialize the previous mouse positions at start so they aren't super large values
	static bool initialized = false;
	if (!initialized)
	{
		prevMousePos.x = x;
		prevMousePos.y = y;
		initialized = true;
	}

	// Set the sensitivity of the camera
	static float sensitivity = .1f;

	if (mouseDown)
	{
		// Rotate the camera
		float deltaX = (x - prevMousePos.x) * (3.141592f / 180.0f);
		float deltaY = (y - prevMousePos.y) * (3.141592f / 180.0f);
		camera->Rotate(deltaY * sensitivity, deltaX * sensitivity);
	}

	// Save the previous mouse position, so we have it for the future
	prevMousePos.x = x;
	prevMousePos.y = y;
}

// --------------------------------------------------------
// Helper method for mouse wheel scrolling.  
// WheelDelta may be positive or negative, depending 
// on the direction of the scroll
// --------------------------------------------------------
void Game::OnMouseWheel(float wheelDelta, int x, int y)
{
	// Add any custom code here...
}
#pragma endregion