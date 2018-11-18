#pragma once

#include <d3d9.h>
#include <d3dx9.h>

/*
	File				: Mesh.h
	Author				: Sloan Kelly
	Purpose				: 

	2006-03-27			: Initial Draft
*/

class CMesh
{
public:

	/*
	Constructors
	*/
	CMesh(void);
	~CMesh(void);

	/*
	Accessors
	*/

	/*
	Draw
	Draws the shape on-screen
	*/
	void Draw(LPDIRECT3DDEVICE9 device, D3DXMATRIX world, D3DXVECTOR3 scale, D3DXVECTOR3 position, D3DXVECTOR3 rotation);
	void Init(LPDIRECT3DDEVICE9 device, char * filename);

private:

	/*
	DirectX attributes. Should have split out the materials / textures
	into a vector
	*/
	LPD3DXMESH m_shape;					// the .x file
	D3DMATERIAL9 * m_materials;			// all the materials
	LPDIRECT3DTEXTURE9 * m_textures;	// all the textures

	/*
	Housekeeping attributes
	*/
	DWORD m_matCount;						// material count

};
