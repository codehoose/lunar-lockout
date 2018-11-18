#include ".\element.h"
#include <d3d9.h>

CElement::CElement(void)
{
	m_mesh = NULL;
	m_isVisible = true; // default to yes - show!

	m_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

CElement::~CElement(void)
{
	if(m_mesh != NULL)
	{
		delete m_mesh;
		m_mesh = NULL;
	}
}

D3DXVECTOR3 CElement::GetPosition()
{
	return D3DXVECTOR3(m_position.x, m_position.y, m_position.z);
}

D3DXVECTOR3 CElement::GetRotation()
{
	return D3DXVECTOR3(m_rotation.x, m_rotation.y, m_rotation.z);
}

void CElement::SetPosition(D3DXVECTOR3 position)
{
	m_position = D3DXVECTOR3(position.x, position.y, position.z);
}

void CElement::SetRotation(D3DXVECTOR3 rotation)
{
	m_rotation = D3DXVECTOR3(rotation.x, rotation.y, rotation.z);
}

void CElement::SetVisible(bool visibility)
{
	m_isVisible = visibility;
}

void CElement::Draw(LPDIRECT3DDEVICE9 device, CCamera * camera)
{
	//mesh.Draw(m_graphics->GetDevice(), m_camera->GetView(), D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	if(m_isVisible)
		m_mesh->Draw(device, camera->GetWorld(), m_scale, m_position, m_rotation);
}

void CElement::Init(LPDIRECT3DDEVICE9 device, char * filename, int id)
{
	m_mesh = new CMesh;
	m_mesh->Init(device, filename);

	m_id = id;
}

int CElement::GetID()
{
	return m_id;
}
