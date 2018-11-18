#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#define GET_COS(a, b)   a = (float)cos(b) // Get the cos angle of b and store it in a.
#define GET_SINE(a, b)  a = (float)sin(b) // Get the sine angle of b and store it in a.

/*
	File				: Camera.h
	Author				: Sloan Kelly
	Purpose				: 

	2006-03-27			: Initial Draft
*/
class CCamera
{
public:
	CCamera(void);
	~CCamera(void);

	D3DXMATRIX GetWorld();
	D3DXMATRIX GetView();
	D3DXMATRIX GetProjection();

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetLooking();
	D3DXVECTOR3 GetUp();
	D3DXVECTOR3 GetRight();

	void Init(LPDIRECT3DDEVICE9 m_device, D3DXVECTOR3 position,
				float ratio, 
				int width, 
				int height, 
				float clipNear,
				float clipFar);
	void Rotate(D3DXVECTOR3 rotation);
	void RotateLeft();
	void RotateRight();
	void SetPosition(D3DXVECTOR3 units);
	void ShowCamera();
	void Reset();

private:

	void OrthoCamera();

	LPDIRECT3DDEVICE9 m_device;

	D3DXVECTOR3 m_lookingat;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_initpos;
	D3DXVECTOR3 m_right;
	D3DXVECTOR3 m_up;

	D3DXMATRIX m_world;
	D3DXMATRIX m_view;
	D3DXMATRIX m_projection;

	int m_width;
	int m_height;
	float m_ratio;
	float m_aspectratio;
	float m_clipNear;
	float m_clipFar;

	float m_angle; // angle of rotation
};
