
// Struct representing the data we expect to receive from earlier pipeline stages
// - Should match the output of our corresponding vertex shader
// - The name of the struct itself is unimportant
// - The variable names don't have to match other shaders (just the semantics)
// - Each variable must have a semantic, which defines its usage
struct VertexToPixel
{
	// Data type
	//  |
	//  |   Name          Semantic
	//  |    |                |
	//  v    v                v
	float4 position		: SV_POSITION;
	float3 normal		: NORMAL;
};

// Struct representing a directional light
struct DirectionalLight
{
	float4 ambientColor;	// The ambient color of the light
	float4 diffuseColor;	// The diffuse color of the light
	float3 direction;		// The direction the light is pointing
};

// Constant Buffer to hold light information
cbuffer lightData : register(b0)
{
	DirectionalLight light;
};

// --------------------------------------------------------
// The entry point (main method) for our pixel shader
// 
// - Input is the data coming down the pipeline (defined by the struct)
// - Output is a single color (float4)
// - Has a special semantic (SV_TARGET), which means 
//    "put the output of this into the current render target"
// - Named "main" because that's the default the shader compiler looks for
// --------------------------------------------------------
float4 main(VertexToPixel input) : SV_TARGET
{
	// Normalize the passed in normal 
	// - Previous transformations may have made it a non-unit vector
	input.normal = normalize(input.normal);

	// Calculate the normalized direction to the light
	float3 directionToTheLight = normalize(-light.direction);

	// Calculate the light amount using the N dot L equation
	// - Use the dot(v1, v2) function with the surface’s normal and the direction to the light
	// - The normal should already be normalized from a previous step
	// - The dot product result can be negative, which will be problematic if we have multiple
	//   lights.Use the saturate() function to clamp the result between 0 and 1
	float lightAmount = saturate(dot(input.normal, directionToTheLight));

	// Return the final surface color based on light amount, diffuse color and ambient color
	// - Scale the light’s diffuse color by the light amount
	// - Add the light’s ambient color
	return (lightAmount * light.diffuseColor) + light.ambientColor;
}