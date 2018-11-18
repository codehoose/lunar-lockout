#include ".\guimenu.h"
#include <d3d9.h>
#include <d3dx9.h>

CGUIMenu::CGUIMenu(void)
{
	m_element = NULL;
	m_device = NULL;
	m_cursor = NULL;
	m_mode = GUIMENU_STANDARD;
	m_millisecs = m_tickcount = 0.0f;
	m_cursortop = 250;
}

CGUIMenu::~CGUIMenu(void)
{
	KillPointers();
	if(m_cursor!=NULL)
	{
		delete m_cursor;
		m_cursor = NULL;
	}
}


void CGUIMenu::Draw()
{
	m_element->Draw();
	if(m_mode == GUIMENU_STANDARD)
	{
		m_cursor->Draw();
	}
}

void CGUIMenu::InitMenu(LPDIRECT3DDEVICE9 device, char * filename, char * cursorfile)
{
	KillPointers();

	if(m_device==NULL)
	{
		m_device = device;
	}
	m_element = new CHUDElement;
	m_element->Init(m_device, filename, 0, 0, 1024, 768);


	if(m_cursor!=NULL)
	{
		delete m_cursor;
	}
	m_cursor = new CHUDElement;

	m_cursortop = 240;
	m_cursor->Init(m_device, cursorfile, m_cursortop, 140, 128, 128);
	m_mode = GUIMENU_STANDARD;

}

void CGUIMenu::InitSplash(LPDIRECT3DDEVICE9 device, char * filename, float millisecs)
{
	KillPointers();

	if(m_device==NULL)
	{
		m_device = device;
	}
	m_element = new CHUDElement;
	m_element->Init(m_device, filename, 0, 0, 1024, 768);
	m_mode = GUIMENU_SPLASH;
	m_millisecs = millisecs;
}

void CGUIMenu::KillPointers()
{
	if(m_element!=NULL)
	{
		delete m_element;
	}
}

int CGUIMenu::Update(float ticks)
{
	switch(m_mode)
	{
		case GUIMENU_SPLASH:
		{
			m_tickcount+=ticks;
			if(m_tickcount>m_millisecs)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		case GUIMENU_STANDARD:
		{
			break;
		}
	}
}

int CGUIMenu::Update(float ticks, int direction, bool selection)
{
	switch(direction)
	{
		case 1:
		{
			m_cursortop-=100;
			if(m_cursortop<240)
				m_cursortop = 240;
			m_cursor->Move(140, m_cursortop);
			break;
		}
		case 2:
		{
			m_cursortop+=100;
			if(m_cursortop>440)
				m_cursortop = 440;
			m_cursor->Move(140, m_cursortop);
			break;
		}

	}

	if(selection && m_cursortop==440)
		return 1;
	else if(selection && m_cursortop==240)
	{
		return 2;
	}
	else if(selection && m_cursortop==340)
	{
		return 3;
	}

}