#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

#include <stdio.h>

#include "Element.h"
#include "Camera.h"
#include "LunarFile.h"


/*
	File				: Board.h
	Author				: Sloan Kelly
	Purpose				: 

	2006-03-27			: Initial Draft
	2006-03-30			: Added enums for future versions and AddPiece(int type...) which is
	                      better than the original that placed it in screen space not BOARD
						  space. Also added m_robotpositions to keep track of where everything is
*/

enum ROBOT_TYPE {ROBOT_NONE, ROBOT_ORANGE, ROBOT_PURPLE, ROBOT_GREEN, ROBOT_BLUE, ROBOT_YELLOW, ROBOT_PLAYER};
enum SELECTION_MODE {SELECT_NONE, SELECT_BOT, SELECT_NEW}; 

class CBoard
{
public:
	CBoard(void);
	~CBoard(void);

	void Init(LPDIRECT3DDEVICE9 device, CCamera * camera);
	void LoadBoard(int boardid);
	void Draw();
	void Update();

	void AddPiece(char * piece, D3DXVECTOR3 pos);
	void CreateCursor(int x, int z);
	void MoveCursor(int direction); // 1 - n, 2 - s, 3 - w, 4 -e 

	void AddPiece(int type, int px, int py);

	int SelectionHit();
	void Release();
	
private:

	void AddElement(D3DXVECTOR3 pos); // add element to scene
	void AddRed(D3DXVECTOR3 pos); // add red square element to scene
	void InitBoard(); // reset all values to 0;
	void UpdateCursor();

	

	void DebugPrint(char * msg);

	float BoardXToScreen(int x);
	float BoardZToScreen(int z);

	int BotAtPosition(int x, int y); // get the 'bot at the current position
	CElement * BotInfo(int id); // return a CElement with the passed in ID

	void MoveNormal(int direction);
	void MoveSelection(int direction);

	void KillBots();

	int OKEast();
	int OKWest();
	int OKNorth();
	int OKSouth();

	int m_curX;
	int m_curZ;

	int m_selX;
	int m_selZ;

	float m_cursorHeight;

	LPDIRECT3DDEVICE9 m_device;
	CCamera * m_camera;
	std::vector <CElement *> m_board;
	std::vector <CElement *> m_pieces;
	CElement * m_cursor;

	int m_robotpositions[5][5];
	int m_selection;
	int m_grabbedbot;
};
