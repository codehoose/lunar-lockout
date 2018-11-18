#pragma once

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "Graphics.h"
#include "Game.h"
#include "HUDElement.h"

/*
	File				: QDEngine.h
	Author				: Sloan Kelly
	Purpose				:

	2006-03-27			: Initial Draft
*/

const int g_iScreenWidth = 1024;
const int g_iScreenHeight = 768;

const bool WINDOWED = false;

CGraphics * m_graphics;
CGame * m_game;

int m_camRot = 0; // 0 - no rotation of camera, 1 - rot to left, 2 - rot to right
int m_moveCursor = 0; // 0 - no move, 1 - north 2 - south 3 - west 4 - east
bool m_selection = false;


/*
	Windows function declarations and variables - DO NOT edit file beyond this point!
*/

void KillPointers(); // used by the engine; don't edit!!

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
LRESULT CALLBACK QDWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
int SetupWindow(HINSTANCE hInstance, char * windowname);
void GetInput();
void FrameMove(float elapsedTime);

float m_tickcount = 0.0f;

WNDCLASSEX windowClass;		// window class
HWND hWND = NULL;
