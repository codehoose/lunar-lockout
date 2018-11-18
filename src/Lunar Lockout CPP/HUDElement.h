#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#ifndef __hudelementH__
#define __hudelementH__

const DWORD tri_fvf=D3DFVF_XYZRHW|D3DFVF_TEX1;

struct RHWVERTEX 
{
    float x, y, z, rhw;  // The transformed(screen space) position for the vertex.
    float tu,tv;         // Texture coordinates
};

class CHUDElement
{
public:
	CHUDElement(void);
	~CHUDElement(void);
	
	bool Init(LPDIRECT3DDEVICE9 device, char * filename, int top, int left, int width, int height);
	void Draw();

	void Move(int posx, int posy);
		

private:

	bool InitVB();

	LPDIRECT3DDEVICE9 m_device;
	IDirect3DTexture9 * m_texture;
	IDirect3DVertexBuffer9 * m_vertbuf;

	int m_vertcount;
	int m_top;
	int m_left;
	int m_height;
	int m_width;

};

#endif // __hudelementH__