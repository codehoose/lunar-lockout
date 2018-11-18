#include ".\qdengine.h"
#include <stdio.h>
#include <windows.h>

/*
	File				: QDEngine.cpp
	Author				: Sloan Kelly
	Purpose				: Main test program for the QDEngine. Most of the code is 
						  stored in the .h file.

	2006-03-27			: Initial Draft
*/


/*
	WinMain
	Entry point for windows apps. Sets up window frame and starts the game by initialising D3D
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG	msg;	
	m_graphics = new CGraphics;
	m_game = new CGame;
	ZeroMemory( &msg, sizeof(msg) );

	SetupWindow(hInstance, "QDEngine");

	ShowCursor(false);

	//m_graphics->Init(hWND, g_iScreenHeight, g_iScreenWidth, true); // windowed
	m_graphics->Init(hWND, g_iScreenHeight, g_iScreenWidth, WINDOWED); // full screen
	m_game->Init(m_graphics, g_iScreenWidth, g_iScreenHeight);

	DXUtil_Timer(TIMER_RESET);

	while (msg.message!=WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);	
			DispatchMessage(&msg);
		}	
		else
		{
			//Call framemove and pass elapsed time from timer
			//g_pD3Dobject->FrameMove(DXUtil_Timer( TIMER_GETELAPSEDTIME ), g_mousex, g_mousey);
			//call render

			float tick = DXUtil_Timer( TIMER_GETELAPSEDTIME );
			
			FrameMove(tick);
			if(m_game->Update(m_camRot, m_moveCursor, m_selection, tick)) // returns 0 until the user quits, then it returns a 1
				PostQuitMessage(0);

			m_graphics->GetDevice()->Clear(0,NULL,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(0x33, 0x33, 0x33), 1.0f,0);
			m_graphics->GetDevice()->BeginScene();

			m_game->Draw();

			m_graphics->GetDevice()->EndScene();
			m_graphics->GetDevice()->Present(NULL,NULL,NULL,NULL); // flip

			//g_pD3Dobject->Render();
		}
	}

	KillPointers();
	ShowCursor(true);
	UnregisterClass("qdwindow", hInstance);
}

LRESULT CALLBACK QDWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//switch on message
	switch(message)
	{
			//case Destroy(if destroy message)
		case WM_DESTROY:
			{
			//call cleanup method
			///cleanup();
			//PostQuit Message this causes the program to quit
			PostQuitMessage(WM_QUIT);
			}
			break;
		case WM_MOUSEMOVE:
		{

			// Retrieve mouse screen position
			int g_mousex =(short)LOWORD(lParam);
			int g_mousey =(short)HIWORD(lParam);

			// Check to see if the left button is held down:
			bool g_bMouseL=wParam & MK_LBUTTON;
			// Check if right button down:
			bool g_bMouseR=wParam & MK_RBUTTON;
			break;

		}

		case WM_KEYUP:
			switch(wParam)
               { 
                  // Close the app if the user presses escape.
		            //case VK_ESCAPE:
                     //PostQuitMessage(0);
				         break;
               }



	}
	//calls the default window message handler
	return (DefWindowProc(hwnd, message, wParam, lParam));
}

void KillPointers()
{
	if(m_graphics != NULL)
	{
		delete m_graphics;
		m_graphics = NULL;
	}

	if(m_game != NULL)
	{
		m_game->Release();
		delete m_game;
		m_game = NULL;
	}

}

int SetupWindow(HINSTANCE hInstance, char * windowname)
{
	windowClass.cbSize			= sizeof(WNDCLASSEX);
	windowClass.style			= CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc		= QDWndProc;
	windowClass.cbClsExtra		= 0;
	windowClass.cbWndExtra		= 0;
	windowClass.hInstance		= hInstance;
	windowClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);			
	windowClass.hCursor			= LoadCursor(NULL, IDC_ARROW);	
	windowClass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	windowClass.lpszMenuName	= NULL;						
	windowClass.lpszClassName	= "qdwindow";
	windowClass.hIconSm			= LoadIcon(NULL, IDI_WINLOGO);	
	if (!RegisterClassEx(&windowClass))
	{
		::MessageBox(::hWND, "Cannot register window.", "Error: Can\'t create window", 0);
		return 0;
	}	

	hWND = CreateWindowEx(NULL, "qdwindow", windowname ,WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_MAXIMIZE,0, 0, 
		g_iScreenWidth,g_iScreenHeight,NULL, NULL, hInstance,	 NULL);	

	if (!hWND)
	{
		::MessageBox(::hWND, "Cannot create window.", "Error: Can\'t create window", 0);
		return 0;
	}
	return 0;
}

void GetInput()
{
	m_camRot = 0;
	m_moveCursor = 0;
	m_selection = false;

	int width = g_iScreenWidth >> 1;
	int height = g_iScreenHeight >> 1; // is bitwise shift quicker than /2 ??

	POINT mousePos;
	GetCursorPos(&mousePos);

	if((mousePos.x < width) && (m_tickcount==0.0f))
	{
		m_camRot  = 1;
	}
	
	if((mousePos.x > width) && (m_tickcount==0.0f))
	{
		m_camRot  = 2;
	}

	if (((GetAsyncKeyState( VK_LEFT) & 0x8000) == 0x8000) && (m_tickcount==0.0f))
	{
		m_moveCursor = 3; // west
	}
	
	if (((GetAsyncKeyState(VK_RIGHT) & 0x8000) == 0x8000) && (m_tickcount==0.0f))
	{
		m_moveCursor = 4; // east
	}
	
	if (((GetAsyncKeyState(VK_UP) & 0x8000) == 0x8000) && (m_tickcount==0.0f))
	{
		m_moveCursor = 1; // north
	}
	
	if (((GetAsyncKeyState(VK_DOWN) & 0x8000) == 0x8000) && (m_tickcount==0.0f))
	{
		m_moveCursor = 2; // south
	}

	if (((GetAsyncKeyState(VK_SPACE ) & 0x8000) == 0x8000) && (m_tickcount==0.0f))
	{
		m_selection = true;
	}

	if (((GetAsyncKeyState(VK_ESCAPE) & 0x8000) == 0x8000))
	{
		m_moveCursor = 5; // back to main menu
	}

	if (((GetAsyncKeyState(VK_DELETE) & 0x8000) == 0x8000))
	{
		m_moveCursor = 9; // back to main menu
	}

	//SetCursorPos(width, height);
}

void FrameMove(float elapsedtime)
{
	using namespace std;
	char buf[2048];
	//sprintf(buf, "Error: %s error description: %s\n",DXGetErrorString9(hr),DXGetErrorDescription9(hr));
	//sprintf(buf, "%f\n", m_tickcount);
	//OutputDebugString(buf);

	m_tickcount += elapsedtime;

	if(m_tickcount > 0.1f)
	{
		m_tickcount=0.0f;
	}
	GetInput();
}