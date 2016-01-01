//--------------------------------------------------------------------------------------
// File: Tutorial06.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer ConstantBuffer : register( b0 )
{
	matrix World;
	matrix View;
	matrix Projection;
	float4 vLightDir;
	float4 vLightColor;
	float4 vOutputColor;
	float vt;
}


//--------------------------------------------------------------------------------------
struct VS_INPUT//struct for input vertex
{
    float4 Pos : POSITION;
    float3 Norm : NORMAL;
};

struct PS_INPUT//struct for input pixel
{
    float4 Pos : SV_POSITION;
    float3 Norm : TEXCOORD0;
	float1 z : TEXCOORD1;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS( VS_INPUT input )
{
    PS_INPUT output = (PS_INPUT)0;
	input.Pos.y += sin((input.Pos.x) * 5.0f + vt * 5) / 5.0f;
    output.Pos = mul( input.Pos, World );
    output.Pos = mul( output.Pos, View );
    output.Pos = mul( output.Pos, Projection );
	float tg= cos((input.Pos.x) * 5.0f + vt * 5);
	int s = 1;
	if (tg < 0)s *= -1;
	float a = sqrt(1 / (1 + tg * tg));
	output.Norm = mul(float3(sqrt(1 - a * a)*s, a, 0), World);
	output.z = output.Pos.z / 20.0f;
    
    return output;
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( PS_INPUT input) : SV_Target
{
    float4 finalColor = 0;
    finalColor += saturate( -dot( (float3)vLightDir, input.Norm) * vLightColor );
    finalColor.a = 1;
	return finalColor;
}


//--------------------------------------------------------------------------------------
// PSSolid - render a solid color
//--------------------------------------------------------------------------------------
float4 PSSolid( PS_INPUT input) : SV_Target
{
    return vOutputColor;
}
