#include "hudelement.h"

CHUDElement::CHUDElement(void)
{
	m_texture = NULL;
	m_vertbuf = NULL;
	m_device = NULL;

	m_vertcount = 0;
	m_height = 0;
	m_width = 0;
	m_left = 0;
	m_top = 0;
}

void CHUDElement::Draw()
{
	HRESULT hr;
	m_device->SetVertexShader(NULL);
	m_device->SetFVF(tri_fvf);

	/*m_device->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_SELECTARG1);
	m_device->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
	m_device->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_DIFFUSE);   //Ignored
	*/
	m_device->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	m_device->SetRenderState(D3DRS_ZENABLE, FALSE);

	hr = m_device->SetTexture(0,m_texture);
	//Bind our Vertex Buffer
	hr = m_device->SetStreamSource(0, m_vertbuf, 0,sizeof(RHWVERTEX)); //Stride
	//Render from our Vertex Buffer
	hr = m_device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_vertcount);

	m_device->SetRenderState(D3DRS_ZENABLE, TRUE);
}

bool CHUDElement::Init(LPDIRECT3DDEVICE9 device, char * filename, int top, int left, int width, int height)
{
	if(FAILED(D3DXCreateTextureFromFile(device, filename, &m_texture)))
	{
		return false;
	}
	else
	{
		m_device = device; // only assign if we're successful
		m_top = top;
		m_left = left;
		m_width = width;
		m_height = height;
		InitVB();
	}


	return true;
}

void CHUDElement::Move(int posx, int posy)
{
	m_top = posy;
	m_left = posx;
	InitVB();
}

bool CHUDElement::InitVB()
{
RHWVERTEX data[]={

   /*{150,400,1,1,0,1},{150,100,1,1,0,0},{450,100,1,1,1,0},
   {150,400,1,1,0,1},{450,100,1,1,1,0},{450,400,1,1,1,1}*/
   {m_left,m_height + m_top,1,1,0,1},{m_left,m_top,1,1,0,0},{m_width + m_left,m_top,1,1,1,0},
   {m_left,m_height + m_top,1,1,0,1},{m_width + m_left,m_top,1,1,1,0},{m_width + m_left ,m_height + m_top,1,1,1,1}


};
int vert_count=sizeof(data)/sizeof(RHWVERTEX);
int byte_count=vert_count*sizeof(RHWVERTEX);
void *vb_vertices;
HRESULT hr;

   m_vertcount=vert_count/3;

   /*if(FAILED(m_device->CreateVertexBuffer(byte_count,        //Length
                                       D3DUSAGE_WRITEONLY,//Usage
                                       tri_fvf,           //FVF
                                       D3DPOOL_MANAGED,   //Pool
                                       &m_vertbuf,        //ppVertexBuffer
                                       NULL)))*/
	if(FAILED(m_device->CreateVertexBuffer(byte_count, D3DUSAGE_WRITEONLY, tri_fvf, D3DPOOL_MANAGED, &m_vertbuf, NULL)))
      return false;
   

   if(FAILED(m_vertbuf->Lock(0, 0, &vb_vertices, 0)))
      return false;

   memcpy( vb_vertices, data,byte_count);

   m_vertbuf->Unlock();


   return true;
}

CHUDElement::~CHUDElement(void)
{
}
