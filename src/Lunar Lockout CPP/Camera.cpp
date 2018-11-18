#include ".\camera.h"

CCamera::CCamera(void)
{
}

CCamera::~CCamera(void)
{
}

/*
	Init
	Set up the camera and the projection matricies
*/
void CCamera::Init(LPDIRECT3DDEVICE9 device, D3DXVECTOR3 position, float ratio, int width, int height, float clipNear, float clipFar)
{
	m_device = device;

	D3DXMatrixIdentity(&m_world);
	m_device->SetTransform(D3DTS_WORLD, &m_world);

	m_lookingat.x = 0.0f;
	m_lookingat.y = 0.0f;
	m_lookingat.z = 0.0f;
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_position = position;
	m_initpos = position;

	D3DXMatrixLookAtLH(&m_view, &m_position, &m_lookingat, &m_up);
    m_device->SetTransform(D3DTS_VIEW, &m_view);

	D3DXMatrixPerspectiveFovLH( &m_projection, ratio, float(width)/float(height), clipNear, clipFar);
    m_device->SetTransform( D3DTS_PROJECTION, &m_projection );
}

void CCamera::SetPosition(D3DXVECTOR3 units)
{
	m_position+=units;
}



D3DXVECTOR3 CCamera::GetLooking()
{
	return D3DXVECTOR3(m_lookingat.x, m_lookingat.y, m_lookingat.z);
}

D3DXVECTOR3 CCamera::GetPosition()
{
	return D3DXVECTOR3(m_position.x, m_position.y, m_position.z);
}

D3DXVECTOR3 CCamera::GetRight()
{
	return D3DXVECTOR3(m_right.x, m_right.y, m_right.z);
}

D3DXVECTOR3 CCamera::GetUp()
{
	return D3DXVECTOR3(m_up.x, m_up.y, m_up.z);
}

D3DXMATRIX CCamera::GetProjection()
{
	return m_projection;
}

D3DXMATRIX CCamera::GetView()
{
	return m_view;
}

D3DXMATRIX CCamera::GetWorld()
{
	return m_world;
}


/*

*/
void CCamera::OrthoCamera()
{
	D3DXMatrixLookAtLH(&m_view, &m_position, &m_lookingat, &m_up);
    m_device->SetTransform(D3DTS_VIEW, &m_view);	
}

void CCamera::ShowCamera()
{
	m_device->SetTransform(D3DTS_WORLD, &m_world);
}

void CCamera::Rotate(D3DXVECTOR3 rotation)
{}

void CCamera::RotateLeft()
{
	m_angle = m_angle + D3DX_PI/6; // add to the angle

	D3DXVECTOR3 newUp(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 newRight(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 newLooking(0.0f, 0.0f, 1.0f); // always looking in ;o)

	D3DXMATRIX matTemp;
	D3DXMatrixIdentity(&matTemp);

	matTemp._11 = newRight.x;
	matTemp._21 = newRight.y;
	matTemp._31 = newRight.z;
	matTemp._41 = -m_position.x;

	matTemp._12 = newUp.x;
	matTemp._22 = newUp.y;
	matTemp._32 = newUp.z;
	matTemp._42 = -m_position.y;

	matTemp._13 = newLooking.x;
	matTemp._23 = newLooking.y;
	matTemp._33 = newLooking.z;
	matTemp._43 = -m_position.z;

	matTemp._14 = 0.0f;
	matTemp._24 = 0.0f;
	matTemp._34 = 0.0f;
	matTemp._44 = 1.0f;

	D3DXMatrixRotationAxis(&matTemp, &m_right, m_angle);

	D3DXVec3TransformCoord(&m_lookingat, &m_lookingat, &matTemp); 
	D3DXVec3TransformCoord(&m_right, &m_right, &matTemp); 

	OrthoCamera();
}

void CCamera::RotateRight()
{
	D3DXMATRIX matRot;
	D3DXMATRIX matTemp;

	D3DXMatrixIdentity(&matRot);
	D3DXMatrixIdentity(&matTemp);

	matTemp._11 = m_position.x;
	matTemp._22 = m_position.y;
	matTemp._33 = m_position.z;

	D3DXMatrixRotationZ(&matRot, D3DX_PI/6);
	D3DXMatrixMultiply(&matRot, &matRot, &matTemp);

	m_position.x = matRot._11;
	m_position.y = matRot._22;
	m_position.z = matRot._33;

	OrthoCamera();
}

void CCamera::Reset()
{
	D3DXMatrixIdentity(&m_world);
	m_device->SetTransform(D3DTS_WORLD, &m_world);

	m_lookingat.x = 0.0f;
	m_lookingat.y = 0.0f;
	m_lookingat.z = 0.0f;
	m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_position = m_initpos;

	D3DXMatrixLookAtLH(&m_view, &m_position, &m_lookingat, &m_up);
    m_device->SetTransform(D3DTS_VIEW, &m_view);

	//D3DXMatrixPerspectiveFovLH( &m_projection, ratio, float(width)/float(height), clipNear, clipFar);
    //m_device->SetTransform( D3DTS_PROJECTION, &m_projection );
}