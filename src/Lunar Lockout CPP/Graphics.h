#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class CGraphics
{
public:
	CGraphics(void);
	~CGraphics(void);

	LPDIRECT3DDEVICE9 GetDevice();

	HRESULT Init(HWND hwnd, int height, int width, bool windowed);
	D3DFORMAT CheckDepthDeviceFormat(D3DFORMAT * depthFormat, D3DFORMAT adapterFormat, int numberFormats);

private:

	LPDIRECT3D9 m_pD3D9;
	LPDIRECT3DDEVICE9 m_pD3DDevice9;

	int m_iBackBufferWidth;
	int m_iBackBufferHeight;
};
