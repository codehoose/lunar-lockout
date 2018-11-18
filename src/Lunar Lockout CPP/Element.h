#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#include "Mesh.h"
#include "Camera.h"

/*
	File				: Element.h
	Author				: Sloan Kelly
	Purpose				: 

	2006-03-27			: Initial Draft
*/

class CElement
{
public:
	CElement(void);
	~CElement(void);

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();

	void SetPosition(D3DXVECTOR3 position);
	void SetRotation(D3DXVECTOR3 rotation);
	void SetVisible(bool visibility);

	void Draw(LPDIRECT3DDEVICE9 device, CCamera * camera);
	void Init(LPDIRECT3DDEVICE9 device, char * filename, int id);

	int GetID();

private:

	CMesh * m_mesh;				// the shape of the element

	D3DXVECTOR3 m_position;		// postion
	D3DXVECTOR3 m_rotation;		// rotation from (0, 0, 0)
	D3DXVECTOR3 m_scale;		// rotation from (0, 0, 0)

	bool m_isVisible;				// determines if we show the shape or not
	int m_id;


};
