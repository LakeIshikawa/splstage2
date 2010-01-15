#pragma once

#define D3DFVF_TL (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

struct D3DTLVERTEX
{
	float fX;
	float fY;
	float fZ;
	float fRHW;
	D3DCOLOR Color;
	float fU;
	float fV;
};

//-----------------------------------------------------------------------------------
//CreateD3DTLVERTEX--Populate a D3DTLVERTEX structure
//-----------------------------------------------------------------------------------
D3DTLVERTEX CreateD3DTLVERTEX (float X, float Y, float Z, float RHW, 
															 D3DCOLOR color, float U, float V)
{
	D3DTLVERTEX v;

	v.fX = X;
	v.fY = Y;
	v.fZ = Z;
	v.fRHW = RHW;
	v.Color = color;
	v.fU = U;
	v.fV = V;

	return v;
}//CreateD3DTLVERTEX
