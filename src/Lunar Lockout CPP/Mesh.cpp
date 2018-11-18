#include ".\mesh.h"

/*
	File				: Mesh.cpp
	Author				: Sloan Kelly
	Purpose				: 

	2006-03-27			: Initial Draft
*/

CMesh::CMesh(void)
{
}

CMesh::~CMesh(void)
{
}

void CMesh::Init(LPDIRECT3DDEVICE9 device, char * filename)
{
	LPD3DXBUFFER pD3DXMtrlBuffer = NULL;
   // Load the mesh from the specified file (no error checking)
	D3DXLoadMeshFromX( filename, D3DXMESH_SYSTEMMEM,
                                   device, NULL,
								   &pD3DXMtrlBuffer, NULL, &m_matCount,
								   &m_shape);

    //Get Materials
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
    //Assign Enough memory for all Textures and materials
	m_materials = new D3DMATERIAL9[m_matCount];
	m_textures =new LPDIRECT3DTEXTURE9[m_matCount];
	//Loop through all materials
	for( DWORD i=0; i<m_matCount; i++ )
    {
        // Copy the material
		m_materials[i] = d3dxMaterials[i].MatD3D;
        // Set the ambient color for the material (D3DX does not do this)
		m_materials[i].Ambient = m_materials[i].Diffuse;
		m_textures[i]=NULL;
		//Create Texture
		D3DXCreateTextureFromFile( device, d3dxMaterials[i].pTextureFilename,&m_textures[i] );
    }

    // Done with the material buffer
    pD3DXMtrlBuffer->Release();
}

void CMesh::Draw(LPDIRECT3DDEVICE9 device, D3DXMATRIX world, D3DXVECTOR3 scale, D3DXVECTOR3 position, D3DXVECTOR3 rotation)
{
	D3DXMATRIX matWorld = world; // copy the world matrix
	D3DXMATRIX matScale;
	D3DXMATRIX matRotation;
	D3DXMATRIX matTranslation;
	
	//set Matrices to identity
	D3DXMatrixIdentity(&matScale);
	D3DXMatrixIdentity(&matRotation);
	D3DXMatrixIdentity(&matTranslation);

	D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);
	D3DXMatrixMultiply(&matWorld,&matWorld,&matScale);

	D3DXMatrixRotationYawPitchRoll(&matRotation, rotation.x, rotation.y, rotation.z);
	D3DXMatrixMultiply(&matWorld,&matWorld,&matRotation);
	
	D3DXMatrixTranslation(&matTranslation, position.x, position.y, position.z);
	D3DXMatrixMultiply(&matWorld,&matWorld,&matTranslation);
	
	device->SetTransform( D3DTS_WORLD, &matWorld );
	device->SetFVF(m_shape->GetFVF());

	device->SetRenderState(D3DRS_LIGHTING, TRUE);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


	for( DWORD i=0; i<m_matCount; i++ )
	{
		device->SetMaterial( &m_materials[i] );
		device->SetTexture( 0, m_textures[i] ); 
		device->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, 0 );
		device->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
		/*device->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_ADD);
		device->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE ); 
		device->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);*/
		

		device->SetTexture(1, NULL); // kill the texture stage so we don't "corrupt" the other meshes
		
		/*if((m_darktexture!=NULL) && (m_isdark))
		{
			device->SetTexture( 1, m_darktexture );
			device->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0 );
			device->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE); 
			device->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
			device->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
		}*/

		m_shape->DrawSubset( i );
	}

}
