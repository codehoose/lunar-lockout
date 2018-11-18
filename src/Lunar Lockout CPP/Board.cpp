#include ".\board.h"

CBoard::CBoard(void)
{
	m_curX = m_curZ = 3; // middle of board
	m_grabbedbot = 0;
}

CBoard::~CBoard(void)
{

}

void CBoard::Release()
{
	m_cursor = NULL;
	delete m_cursor;

	m_pieces.clear();
	m_board.clear();
}

void CBoard::Init(LPDIRECT3DDEVICE9 device, CCamera * camera)
{
	m_device = device;
	m_camera = camera;

	for(int z=0; z<5; z++)
	{
		for(int x=0; x<5; x++)
		{
			float offx = -8.0f + (x*4.0f);
			float offz = 8.0f - (z*4.0f);
			if((x==2) && (z==2))
			{
				AddRed(D3DXVECTOR3(offx, 0.0f, offz));
			}
			else
			{
				AddElement(D3DXVECTOR3(offx, 0.0f, offz));
			}
		}
	}

	InitBoard(); // clear the board and set up some internal vars
}
void CBoard::AddElement(D3DXVECTOR3 pos)
{
	CElement * val = new CElement;
	val->Init(m_device, "square.x", 0);
	val->SetPosition(pos);
	m_board.push_back(val);
}

void CBoard::AddRed(D3DXVECTOR3 pos)
{
	CElement * val = new CElement;
	val->Init(m_device, "red.x", 0);
	val->SetPosition(pos);
	m_board.push_back(val);
}

void CBoard::AddPiece(char * piece, D3DXVECTOR3 pos)
{
	CElement * val = new CElement;
	val->Init(m_device, piece, 0);
	val->SetPosition(pos);
	m_pieces.push_back(val);
}

void CBoard::AddPiece(int type, int px, int py)
{
	CElement * val = new CElement;

	switch(type)
	{
	case ROBOT_BLUE:
		val->Init(m_device, "blue.x", type);
		break;
	case ROBOT_GREEN:
		val->Init(m_device, "green.x", type);
		break;
	case ROBOT_ORANGE:
		val->Init(m_device, "orange.x", type);
		break;
	case ROBOT_PURPLE:
		val->Init(m_device, "purple.x", type);
		break;
	case ROBOT_YELLOW:
		val->Init(m_device, "yellow.x", type);
		break;
	case ROBOT_PLAYER:
		val->Init(m_device, "player.x", type);
		break;
	}

	float nx = BoardXToScreen(px);
	float nz = BoardZToScreen(py);

	val->SetPosition(D3DXVECTOR3(nx, 1.0f, nz));
	m_robotpositions[px][py] = type;

	m_pieces.push_back(val);

}

void CBoard::InitBoard()
{
	m_selection	= m_curX = m_curZ = m_grabbedbot = 0;
	m_cursorHeight = 1.2f;

	KillBots();

	for(int y=0; y<5; y++)
	{
		for(int x=0; x<5; x++)
		{
			m_robotpositions[x][y] = ROBOT_NONE;
		}
	}
}

void CBoard::CreateCursor(int x, int z)
{
	float nx = BoardXToScreen(x);
	float nz = BoardZToScreen(z);

	m_curX = x;
	m_curZ = z;

	m_cursor = new CElement;
	m_cursor->Init(m_device, "cursor.x", 0);
	m_cursor->SetPosition(D3DXVECTOR3(nx, 1.2f, nz));
}

void CBoard::Update()
{
	UpdateCursor();
}

int CBoard::BotAtPosition(int x, int y)
{
	m_grabbedbot = m_robotpositions[x][y];
	return m_grabbedbot;
}

CElement * CBoard::BotInfo(int id)
{
	for(int i=0; i<m_pieces.size(); i++)
	{
		if(id==m_pieces[i]->GetID())
		{
			return (CElement *)m_pieces[i];
		}
	}

	return NULL;
}


int CBoard::SelectionHit()
{
	m_cursorHeight = 1.2f;

	switch(m_selection)
	{
	case SELECT_NONE: // nothing is selected, so we can grab a bot and drag it around
		if(m_robotpositions[m_curX][m_curZ]!=ROBOT_NONE)
		{
			m_selX = m_curX;
			m_selZ = m_curZ;
			m_selection = SELECT_BOT;
			m_cursorHeight = 2.0f;
			m_grabbedbot = m_robotpositions[m_curX][m_curZ];
			//DebugPrint("Selected bot");
		}
		break;
	case SELECT_BOT: // now that we've grabbed a bot we can set it down in a blank square
					 // we'll let the player put the piece back on the same square too!
		if(m_robotpositions[m_curX][m_curZ]==ROBOT_NONE || m_robotpositions[m_curX][m_curZ]==m_grabbedbot)
		{
			m_selection = SELECT_NONE;
			m_robotpositions[m_selX][m_selZ] = ROBOT_NONE; // do it this way round! blank out the SELECTED
			m_robotpositions[m_curX][m_curZ] = m_grabbedbot; // square and then place the piece. This way
															 // users can re-place pieces where they were
			float nx = BoardXToScreen(m_curX);
			float nz = BoardZToScreen(m_curZ);
			CElement * curBot = BotInfo(m_grabbedbot);
			curBot->SetPosition(D3DXVECTOR3(nx, 1.0f, nz));

			if(m_curX==2 && m_curZ==2 && m_grabbedbot==ROBOT_PLAYER)
			{
				return 1;
			}

			m_grabbedbot = 0;
		}
		break;
	case SELECT_NEW: // uhm ... dunno :o)
		//do nothing yet
		break;
	}

	return 0;
}

void CBoard::UpdateCursor()
{
	float nx = BoardXToScreen(m_curX);
	float nz = BoardZToScreen(m_curZ);

	if(!m_grabbedbot)
	{
		m_cursor->SetPosition(D3DXVECTOR3(nx, m_cursorHeight, nz));
	}
	else
	{
		CElement * bot = BotInfo(m_grabbedbot);
		if(!bot)
		{
			m_cursor->SetPosition(D3DXVECTOR3(nx, m_cursorHeight, nz));
		}
		else
		{
			bot->SetPosition(D3DXVECTOR3(nx, m_cursorHeight, nz));
			bot->Draw(m_device, m_camera);
		}
	}
}

float CBoard::BoardXToScreen(int x)
{
	float offx = -8.0f + (x*4.0f);
	return offx;
}

float CBoard::BoardZToScreen(int z)
{
	float offz = 8.0f - (z*4.0f);
	return offz;
}

void CBoard::MoveCursor(int direction)
{

	if(!m_grabbedbot)
	{
		MoveNormal(direction);
	}
	else

	{
		MoveSelection(direction);
	}
}

int CBoard::OKEast()
{
	int location = -1;
	int i = m_curX+1;

	//for(int i=m_selX+1; i<5; i++)

	while(i<5 && location<0)
	{
		if(m_robotpositions[i][m_selZ]!=ROBOT_NONE || m_robotpositions[i][m_selZ]==m_grabbedbot)
		{
			if(m_robotpositions[i][m_selZ]==m_grabbedbot)
			{
				location = i;
			}
			else
			{
				location = i-1;
			}
		}
		i++;
	}
	return location;
}

int CBoard::OKWest()
{
	int location = -1;
	int i = m_curX-1;

	//for(int i=m_selX+1; i<5; i++)

	while(i>=0 && location<0)
	{
		if(m_robotpositions[i][m_selZ]!=ROBOT_NONE || m_robotpositions[i][m_selZ]==m_grabbedbot)
		{
			if(m_robotpositions[i][m_selZ]==m_grabbedbot)
			{
				location = i;
			}
			else
			{
				location = i+1;
			}
		}
		i--;
	}
	return location;
}

int CBoard::OKNorth()
{
	int location = -1;
	int i = m_curZ-1;

	//for(int i=m_selX+1; i<5; i++)

	while(i>=0 && location<0)
	{
		if(m_robotpositions[m_selX][i]!=ROBOT_NONE || m_robotpositions[m_selX][i]==m_grabbedbot)
		{
			if(m_robotpositions[m_selX][i]==m_grabbedbot)
			{
				location = i;
			}
			else
			{
				location = i+1;
			}
		}
		i--;
	}
	return location;
}

int CBoard::OKSouth()
{
	int location = -1;
	int i = m_curZ+1;

	//for(int i=m_selX+1; i<5; i++)

	while(i<5 && location<0)
	{
		if(m_robotpositions[m_selX][i]!=ROBOT_NONE || m_robotpositions[m_selX][i]==m_grabbedbot)
		{
			if(m_robotpositions[m_selX][i]==m_grabbedbot)
			{
				location = i;
			}
			else
			{
				location = i-1;
			}
		}
		i++;
	}
	return location;
}

void CBoard::MoveSelection(int direction)
{
	switch(direction)
	{
		case 0:
			// do nothing
				break;
		case 1: // north
			{
				int newZ = OKNorth();
				if(newZ>=0)
				{
					m_curZ = newZ;
				}
				break;
			}
		case 2: // south
			{
				int newZ = OKSouth();
				if(newZ>=0)
				{
					m_curZ = newZ;
				}
				break;
			}
		case 3: //west
			{
				int newX = OKWest();
				if(newX>=0)
				{
					m_curX = newX;
				}
				break;
			}
		case 4: // east
			{
				int newX = OKEast();
				if(newX>0)
				{
					m_curX = newX;
				}
				break;
			}
	}


}

void CBoard::MoveNormal(int direction)
{
	switch(direction)
	{
		case 0:
			// do nothing
			break;
		case 1: // north
			{
				m_curZ--;
				if(m_curZ <= 0)
					m_curZ = 0;
				break;
			}
		case 2: // south
			{
				m_curZ++;
				if(m_curZ >= 4)
					m_curZ = 4;
				break;
			}
		case 3: //west
			{
				m_curX--;
				if(m_curX <=0)
					m_curX = 0;
				break;
			}
		case 4: // east
			{
				m_curX++;
				if(m_curX >=4)
					m_curX = 4;
				break;
			}
	}
}

void CBoard::Draw()
{
	for(int i=0; i<m_board.size(); i++)
	{
		m_board[i]->Draw(m_device, m_camera);
	}

	for(int i=0; i<m_pieces.size(); i++)
	{
		m_pieces[i]->Draw(m_device, m_camera);
	}

	if(!m_grabbedbot)
		m_cursor->Draw(m_device, m_camera);
}

void CBoard::DebugPrint(char * msg)
{
	//using namespace std;
	//char buf[2048];
	////sprintf(buf, "Error: %s error description: %s\n",DXGetErrorString9(hr),DXGetErrorDescription9(hr));
	//sprintf(buf, "%f\n", msg);
	//OutputDebugString(buf);

}

void CBoard::LoadBoard(int boardid)
{
	string lines[5];
	InitBoard();
	CLunarFile boardfile;
	boardfile.ReadLunar(boardid, lines);

	for(int row=0; row<5; row++)
	{
		for(int col=0; col<5; col++)
		{
			switch(lines[row][col])
			{
				case '-':
				{
				// ignore for now
					break;
				}
				case 'r':
				{
					AddPiece(ROBOT_PLAYER, col, row);
					break;
				}
				case 'o':
				{
					AddPiece(ROBOT_ORANGE, col, row);
					break;
				}
				case 'p':
				{
					AddPiece(ROBOT_PURPLE, col, row);
					break;
				}
				case 'y':
				{
					AddPiece(ROBOT_YELLOW, col, row);
					break;
				}
				case 'g':
				{
					AddPiece(ROBOT_GREEN, col, row);
					break;
				}
			}
		}
	}
}

void CBoard::KillBots()
{
	m_pieces.clear();
}