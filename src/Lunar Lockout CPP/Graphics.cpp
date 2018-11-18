#include ".\graphics.h"

CGraphics::CGraphics(void)
{
	m_pD3D9 = NULL;
	m_pD3DDevice9 = NULL;
}

CGraphics::~CGraphics(void)
{
	if(m_pD3D9 != NULL)
	{
		m_pD3D9->Release();
		m_pD3D9 = NULL;
	}

	if(m_pD3DDevice9 != NULL)
	{
		m_pD3DDevice9->Release();
		m_pD3DDevice9 = NULL;
	}
}

LPDIRECT3DDEVICE9 CGraphics::GetDevice()
{
	return m_pD3DDevice9;
}

HRESULT CGraphics::Init(HWND hwnd, int height, int width, bool windowed)
{
	//set memeber varaibles backbuffer width and backbuffer height
	//to width and height passed in.
	m_iBackBufferWidth=width;
	m_iBackBufferHeight=height;

	// set up camera to default position is space, pointing at the
	// origin. With y-axis positive being "up"

	//Create D3DObject with the current SDK version passed in
	m_pD3D9=Direct3DCreate9(D3D_SDK_VERSION);

	//if pointer to a D3DObject is NULL then something has went wrong
	//return E_FAIL to the caller
	if (m_pD3D9==NULL)
		return E_FAIL;

	//create displaymode structure
	D3DDISPLAYMODE d3ddisplay;

	//get the display mode of the current graphics card and pass in displaymode
	//structure, this fills the structure with values that describe the graphics
	//display
	m_pD3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddisplay);
	//create an array of common depth/stencil buffer formats, you can add others to this array 
	D3DFORMAT StencilDepthFormats[]={D3DFMT_D16,D3DFMT_D32,D3DFMT_D24X8};
	// call CheckDepthStencil to check the buffer format, pass in the array created above,
	// the display format, and the size of the array. This function returns a D3DFORMAT
	// this will be our depth buffer format
	//NB if you add more stencil buffer formats to the array remeber to increase the size of 
	// the last parameter passed to this function
	D3DFORMAT SupportedStencil=CheckDepthDeviceFormat(StencilDepthFormats,d3ddisplay.Format,3);
	//if the return D3DFormat is -1 then no formats have been found that support this device,
	//you can increase the number of formats in the array and recompile and try again.
	if (SupportedStencil==-1)
		return E_FAIL;
	//Creat D3DPRESENT_PARAMETERS structure
	D3DPRESENT_PARAMETERS d3dparameters;
	//ZeroMemory this function sets all the values of the passed structure to zero
	ZeroMemory(&d3dparameters, sizeof(d3dparameters));
	//set backbuffer width and height
	d3dparameters.BackBufferHeight=m_iBackBufferHeight;
	d3dparameters.BackBufferWidth=m_iBackBufferWidth;
	//set the backbuffre format to the one held in the DIsplaymode structure
	d3dparameters.BackBufferFormat=d3ddisplay.Format;
	//set swapeffect to Discard
	d3dparameters.SwapEffect=D3DSWAPEFFECT_DISCARD;
	//Enable for depth buffer
    d3dparameters.EnableAutoDepthStencil = TRUE;
	//set depth buffer to SuportStencil 
    d3dparameters.AutoDepthStencilFormat =SupportedStencil;
	//set windowed mode
	d3dparameters.Windowed=windowed;
	//d3dparameters.Windowed=false;

	//CreateDevice - Creates the Direct3D Device.
	//Check the Directx Docs for explanations of each of these parameters
	//At the moment we are using software vertex processing for compatability
	//but if you wanted Hardware vertex processing then you would have to use the 
	//D3D object to check the capabilites of the garphics card
	//If this fails then return E_FAIL to the caller
	if (FAILED(m_pD3D9->CreateDevice(D3DADAPTER_DEFAULT, 
		D3DDEVTYPE_HAL, hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dparameters, &m_pD3DDevice9)))
	{
		return E_FAIL;
	}
	// Turn off culling, so we see the front and back of the triangle
	m_pD3DDevice9->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
	m_pD3DDevice9->SetRenderState(D3DRS_ZENABLE,D3DZB_TRUE);

	//if we get to this point everything went well we will return S_OK
	return S_OK;
}

D3DFORMAT CGraphics::CheckDepthDeviceFormat(D3DFORMAT * depthFormat, D3DFORMAT adapterFormat, int numberFormats)
{
	//will hold our support depth buffer format
	D3DFORMAT SupportFormat=(D3DFORMAT)-1;
	//used to hold the return value from CheckDeviceFormat function, if the format is supported
	//then it will S_OK if not it will be E_FAIL
	HRESULT hr=S_OK;
	//loop through all value held in array
    for (int i=0;i<numberFormats;i++)
	{
		//CheckDeviceFormat, Used to check to see if a depth format is support by the
		//Graphics Card this return S_OK if the format is support or E_FAIL if is not
		hr= m_pD3D9->CheckDeviceFormat( D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			adapterFormat,
			D3DUSAGE_DEPTHSTENCIL,
			D3DRTYPE_SURFACE,
			depthFormat[i]);
		//if the HR is S_OK then set the supported format to the one in  the array that is
		//supported by the graphics card, then return supportedformat to the calling method
		if(SUCCEEDED(hr)){
			SupportFormat=depthFormat[i];
			return SupportFormat;
		}
	}

	//return SupportFormat if no format was support this should still be -1
	return SupportFormat;
}