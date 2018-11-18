#pragma once

#include "HUDElement.h"

enum GUIMENU_TYPE {GUIMENU_SPLASH, GUIMENU_STANDARD};

class CGUIMenu
{
public:
	CGUIMenu(void);
	~CGUIMenu(void);

	int Update(float ticks);
	int Update(float ticks, int direction, bool selection);
	void Draw();

	void InitSplash(LPDIRECT3DDEVICE9 device, char * filename, float millisecs);
	void InitMenu(LPDIRECT3DDEVICE9 device, char * filename, char * cursorfile);

private:

	void KillPointers();

	LPDIRECT3DDEVICE9 m_device;
	float m_millisecs;
	float m_tickcount;
	int m_mode;
	int m_cursortop;
	CHUDElement * m_element;
	CHUDElement * m_cursor;
};
