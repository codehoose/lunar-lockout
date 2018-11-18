#include ".\game.h"
#include "GUIMenu.h"

#include <string>

CGame::CGame(void)
{
	m_graphics = NULL;
	m_board = NULL;
	m_camera = NULL;
	m_gui = NULL;
	m_hud = NULL;
	m_level = NULL;

	m_boardid = 1;
	m_mode = 0;
}

CGame::~CGame(void)
{
	if(m_graphics != NULL)
	{
		//delete m_graphics;
		//m_graphics = NULL;
	}

	if(m_board != NULL)
	{
		delete m_board;
		m_board = NULL;
	}

	if(m_camera != NULL)
	{
		delete m_camera;
		m_camera = NULL;
	}

	if(m_gui != NULL)
	{
		delete m_gui;
		m_gui = NULL;
	}

	if(m_hud != NULL)
	{
		delete m_hud;
		m_hud = NULL;
	}


	if(m_backdrop!=NULL)
	{
		delete m_backdrop;
	}

	if(m_level!=NULL)
	{
		delete m_level;
	}
}


void CGame::Release()
{
	if(m_board != NULL)
	{
 		m_board->Release();
		m_board = NULL;
	}

	if(m_camera != NULL)
	{
		delete m_camera;
		m_camera = NULL;
	}
}

void CGame::Init(CGraphics * gfx, int width, int height)
{
	m_graphics = gfx;


    // Set up a white, directional light.
    // Note that many Lights may be active at a time (but each one slows down
    // the rendering of our scene). However, here we are just using one. Also,
    // we need to set the D3DRS_LIGHTING renderstate to enable lighting
    D3DLIGHT9 light;
	D3DCOLORVALUE specular;
	specular.r = 0.2f;
	specular.g = 0.2f;
	specular.b = 0.2f;
	specular.a = 0.2f;
    ZeroMemory( &light, sizeof(D3DLIGHT9) );
	light.Type       =  D3DLIGHT_POINT; // D3DLIGHT_DIRECTIONAL;
    light.Diffuse.r  = 1.0f;
    light.Diffuse.g  = 1.0f;
    light.Diffuse.b  = 1.0f;

	light.Specular = specular;//light.Diffuse;
	//light.Attenuation0 = 0.0f;

	light.Position = D3DXVECTOR3(0.0f, 20.0f, -15.0f);
	light.Specular = specular;
	light.Direction= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    light.Range       = 1.0f;
    m_graphics->GetDevice()->SetLight( 0, &light );
	m_graphics->GetDevice()->LightEnable( 0, TRUE );

    D3DLIGHT9 light2;
	D3DCOLORVALUE specular2;
	specular2.r = 0.01f;
	specular2.g = 0.01f;
	specular2.b = 0.01f;
	specular2.a = 0.01f;
    ZeroMemory( &light2, sizeof(D3DLIGHT9) );
	light2.Type       = D3DLIGHT_POINT;

	light2.Ambient.r = 0.10f;
	light2.Ambient.g = 0.10f;
	light2.Ambient.b = 0.10f;

    light2.Diffuse.r  = 0.10f;
    light2.Diffuse.g  = 0.10f;
    light2.Diffuse.b  = 0.20f;

	light2.Position = D3DXVECTOR3(0.0f, 100.0f, -500.0f);
	light2.Specular = specular2;
	light2.Range       = 1.0f;
	light2.Direction= D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	m_graphics->GetDevice()->SetLight( 0, &light2 );
	m_graphics->GetDevice()->LightEnable( 0, TRUE );
    m_graphics->GetDevice()->SetRenderState( D3DRS_LIGHTING, TRUE );
	//m_pD3DDevice9->SetRenderState( D3DRS_LIGHTING, FALSE );

	 
    // Finally, ambient light.
    m_graphics->GetDevice()->SetRenderState( D3DRS_AMBIENT, 0x00909090 );
	//m_pD3DDevice9->SetRenderState( D3DRS_AMBIENT, 0x00000000 );




	m_board = new CBoard;
	m_camera = new CCamera;
	m_hud = new CHUDElement;
	m_backdrop = new CHUDElement;
	m_gui = new CGUIMenu;
	m_about = new CHUDElement;
	m_level = new CHUDElement;

	m_camera->Init(m_graphics->GetDevice(), D3DXVECTOR3(0.0f, 20.0f, -20.0f), D3DX_PI/4, width, height, 1.0f, 100.0f);
	m_board->Init(m_graphics->GetDevice(), m_camera);
	m_hud->Init(m_graphics->GetDevice(), "test.png", 0, 0, 1024, 768);
	m_backdrop->Init(m_graphics->GetDevice(), "backdrop.jpg", 0, 0, 1024, 768);
	m_about->Init(m_graphics->GetDevice(), "about.jpg", 0, 0, 1024, 768);
	m_level->Init(m_graphics->GetDevice(), "1.png", 0, 1024-107, 107, 77);

	


	m_board->CreateCursor(0, 0);
	m_board->LoadBoard(m_boardid);
	
	m_gui->InitSplash(m_graphics->GetDevice(), "splash.jpg", 3);
	m_mode = GAMEMODE_SPLASH;


}

void CGame::Draw()
{
	switch(m_mode)
	{
		case GAMEMODE_PLAYING:
		{
			m_backdrop->Draw();
			m_board->Draw();
			m_hud->Draw();
			m_level->Draw();
			
			break;
		}

		case GAMEMODE_SPLASH:
		{
			m_gui->Draw();
			break;
		}

		case GAMEMODE_MENU:
		{
			m_gui->Draw();
			break;
		}
		
		case GAMEMODE_ABOUT:
		{
			m_about->Draw();
			break;
		}
	}
	
}

void CGame::ShowMenu()
{

}

void CGame::ShowSplash()
{
}

int CGame::Update(int camerarotation, int movecursor, bool selection, float tick)
{
	switch(m_mode)
	{
		case GAMEMODE_MENU:
		{
			// do menu
			int result = m_gui->Update(tick, movecursor, selection);
			switch(result)
			{
				case 1:
				{
					return 1;
					break;
				}
				case 2:
				{
					m_mode = GAMEMODE_PLAYING;
					break;
				}
				case 3:
				{
					m_mode = GAMEMODE_ABOUT;
					break;
				}
			};
			break;
		}

		case GAMEMODE_PLAYING:
		{
			if(movecursor==5) // special case, gets us back to the main menu when we hit ESCAPÉ! (ess-kay-pay!)
				m_mode = GAMEMODE_MENU;
			else
				UpdateMovement(camerarotation, movecursor, selection, tick);
			break;
			if(m_boardid>10)
			{
				return 1; // quit the game if we get to 10
			}
		}

		case GAMEMODE_SPLASH:
		{
			int result = m_gui->Update(tick);
			if(result==1)
			{
				//m_mode = GAMEMODE_PLAYING;
				m_mode = GAMEMODE_MENU;
				m_gui->InitMenu(m_graphics->GetDevice(), "menu.jpg", "cursor.png");
			}
			break;
		}

		case GAMEMODE_ABOUT:
		{
			if(selection)
				m_mode = GAMEMODE_MENU;
		}
	}

	return 0;
}

void CGame::UpdateMovement(int camerarotation, int movecursor, bool selection, float tick)
{
	switch(camerarotation)
	{
		case 0:
			// no rotation
			break;
		case 1:
			{
				//m_camera->RotateLeft();
				break;
			}
		case 2:
			{
				//m_camera->RotateRight();
				break;
			}
	}

	if(selection)
	{
		// if the player landed in the middle -- move onto the next board!
		if(m_board->SelectionHit())
		{
			m_boardid++;
			if(m_boardid<=10)
			{
				m_board->LoadBoard(m_boardid);
				using namespace std;
				string s = ".png";
				char tempBuf[8];
				itoa(m_boardid, tempBuf, 10);
				string s2(tempBuf);
				s = s2 + s;
				m_level->Init(m_graphics->GetDevice(), (char*)s.c_str(), 0, 1024-107, 107, 77);
			}
		}
	}

	if(movecursor==9)
		m_board->LoadBoard(m_boardid);
	else
		m_board->MoveCursor(movecursor);
	m_board->Update();
}