#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "Graphics.h"
#include "Camera.h"
#include "GUIMenu.h"
#include "HUDElement.h"
#include "Board.h"
#include "dxutil.h"

/*
	File				: Game.h
	Author				: Sloan Kelly
	Purpose				: 

	2006-03-27			: Initial Draft
*/

enum GAME_MODE { GAMEMODE_PLAYING, GAMEMODE_SPLASH, GAMEMODE_MENU, GAMEMODE_ABOUT  };

class CGame
{
public:
	CGame(void);
	~CGame(void);

	void Init(CGraphics * gfx, int width, int height);
	void Draw();
	int Update(int cameraRotation, int movecursor, bool selection, float tick);

	void UpdateMovement(int cameraRotation, int movecursor, bool selection, float tick);

	void MainLoop();
	void ShowSplash();
	void ShowMenu();
	void Release();

private:

	CGraphics * m_graphics;				// the graphics abstraction class
	CCamera * m_camera;
	CBoard * m_board;					// the game board
	CGUIMenu * m_gui;
	CHUDElement * m_hud;
	CHUDElement * m_about;
	CHUDElement * m_backdrop;
	CHUDElement * m_level;

	int m_mode; // <-- mode the game is in
	int m_boardid; // <-- the current board number
};
