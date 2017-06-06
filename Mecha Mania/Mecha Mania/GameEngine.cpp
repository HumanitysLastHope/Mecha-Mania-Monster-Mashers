#include "GameEngine.h"
#include "GameState.h"
#include "GettingPlayerMovesState.h"
#include "ExecutingCMDState.h"
#include "MovingBulletsState.h"
#include "Mine.h"
#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>
#include <regex> // GEREX
#include <cstdlib> 
#include <ctime> 
#include <iostream>
#include "Util.h"

HANDLE g_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);



void set_console_size(HANDLE screen_buffer, SHORT width, SHORT height)
{
	COORD const size = { width, height };
	BOOL success;

	SMALL_RECT const minimal_window = { 0, 0, 1, 1 };
	success = SetConsoleWindowInfo(screen_buffer, TRUE, &minimal_window);

	success = SetConsoleScreenBufferSize(screen_buffer, size);

	SMALL_RECT const window = { 0, 0, size.X - 1, size.Y - 1 };
	success = SetConsoleWindowInfo(screen_buffer, TRUE, &window);

}

void setFontSize(int FontSize)
{
	CONSOLE_FONT_INFOEX info = { 0 };
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = FontSize; // leave X as zero
	info.FontWeight = FW_NORMAL;
	wcscpy_s(info.FaceName, sizeof(L"Lucida Console"), L"Lucida Console");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
}

CGameEngine::CGameEngine(int _playerCount) :
	m_Player1({ 0,0 }, NORTH, &m_Level, 1),
	m_Player2({ 0,0 }, NORTH, &m_Level, 2),
	m_Player3({ 0,0 }, NORTH, &m_Level, 3),
	m_Player4({ 0,0 }, NORTH, &m_Level, 4),
	m_pstateExecuting(new ExecutingCMDState),
	m_pstateGetInput(new CGettingPlayerMovesState),
	m_pstateMovBullet(new CMovingBulletsState)
{
	playerAliveCount = _playerCount;

	if (playerAliveCount == 4)
	{
		m_PlayerList = { m_Player1, m_Player2, m_Player3, m_Player4 };

		m_CommandOrder.push_back(0);
		m_CommandOrder.push_back(1);
		m_CommandOrder.push_back(2);
		m_CommandOrder.push_back(3);


	}
	else if (playerAliveCount == 3)
	{
		m_PlayerList = { m_Player1, m_Player2, m_Player3 };
		m_CommandOrder.push_back(0);
		m_CommandOrder.push_back(1);
		m_CommandOrder.push_back(2);

		//m_Player3 = nullptr;
	}
	else
	{
		m_PlayerList = { m_Player1, m_Player2 };
		m_CommandOrder.push_back(0);
		m_CommandOrder.push_back(1);
	}

	//creates a random number so a random map can be chosen


	
	srand((unsigned)time(0));
	int random_integer = (rand() % 4) + 1;
	

	LoadBoard(random_integer, _playerCount);

	

	inGetState = true;
	ChangeState(m_pstateGetInput);
	m_pstateGetInput->ResetZ();
}


CGameEngine::~CGameEngine()
{
	//delete m_pCurGameState;
	for (auto it = m_vecpBulletList.begin(); it != m_vecpBulletList.end(); ++it)
	{
		delete (*it);
	}
	for (int _iY = 0; _iY < 10; ++_iY)
	{
		for (int _iX = 0; _iX < 10; ++_iX)
		{
			if (m_Level.GetTile(_iX, _iY).GetMine() != nullptr)
			{
				CMine* temp = m_Level.GetTile(_iX, _iY).GetMine();
				m_Level.GetTile(_iX, _iY).SetMine(nullptr);
				delete temp;
			}
		}
	}

	delete m_pstateExecuting;
	delete m_pstateGetInput;
	delete m_pstateMovBullet;

}

void CGameEngine::Step()
{

	playerAliveCount = 0;
	for (int l = 0; l < m_PlayerList.size(); l++) // CHECK DEATH
	{
		
		m_PlayerList[l].bDead = m_PlayerList[l].CheckDeath();

		if (m_PlayerList[l].bDead == false)
		{
			playerAliveCount++;

			if (playerAliveCount == 1)
			{
				m_pWinner = &m_PlayerList[l];
			}
			else
			{
				m_pWinner = nullptr;
			}
		}
	}
	if (playerAliveCount == 0)
	{
		inGetState = true;
	}

	PitCheck();


	m_pCurGameState->Step(this);

	BulletCollisionTest();

	if (m_bBulletsToDestroy)
	{
		ActuallyDestroyBullets();
	}

	if (m_pCurGameState == m_pstateExecuting)
	{
		PrintBattleActionText();
	}

	
}

bool CGameEngine::PitCheck()
{
	bool _bReturn = false;

	// Cycles through the whole grid for each tile and checks and excutes behaviour if a Mecha is standing on pit
	for (int _iY = 0; _iY < 10; ++_iY)
	{
		for (int _iX = 0; _iX < 10; ++_iX)
		{
			// Checks pit
			if (m_Level.GetTile(_iX, _iY).GetEnvironment() == PIT && m_Level.GetTile(_iX, _iY).GetMecha() != nullptr)
			{
				m_Level.GetTile(_iX, _iY).GetMecha()->ChangeHealth(-5);
				ActionText('P', m_Level.GetTile(_iX, _iY).GetMecha(), true);
				m_Level.GetTile(_iX, _iY).SetMecha(nullptr);
				_bReturn = true;
			}
		}
	}
	return _bReturn;
}

void CGameEngine::WaterCheck(CPlayer* _pPlayer)
{
	if (m_Level.GetTile(_pPlayer->GetMecha()->GetGridPosition().m_iX, _pPlayer->GetMecha()->GetGridPosition().m_iY).GetEnvironment() == WATER)
	{
 		_pPlayer->GetMecha()->ChangeHealth(-1);

		if (_pPlayer->GetMecha()->GetHealth() <= 0)
		{
			ActionText('W', _pPlayer->GetMecha(), true);

		}
		else
		{
			ActionText('W', _pPlayer->GetMecha(), false);
		}

	}
}


// Moves the cursor position to input coods.
//void GotoXY(int _iX, int _iY) {
//	COORD point;
//	point.X = _iX;
//	point.Y = _iY;
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
//}

// A minimal Int value that can be inputted by the player, a maximum Int value that can be inputted by the player, a personalised error message
int inputValidator(const int &_inputMin, const int &_inputMax, const std::string &_sErrorMsg, int _iX, int _iY, int _ErrorMsgX, int _ErrorMsgY)
{
	std::string input;
	std::regex integer("[[:digit:]]+");
	while (true)
	{
		input = _getch();

		if ((regex_match(input, integer)) && (_inputMin <= stoi(input)) && (_inputMax >= stoi(input)))
		{
			return(stoi(input));
		}
		else
		{
			GotoXY(_iX, _iY);
			std::cout << " ]           ";
			GotoXY(_ErrorMsgX, _ErrorMsgY);
			std::cout << _sErrorMsg << std::endl;
			GotoXY(_iX, _iY);
		}
	}
}


// A minimal Int value that can be inputted by the player, a maximum Int value that can be inputted by the player, a personalised error message
void DrawGrid(int _iTopX, int _iTopY, int _iBottomX, int _iBottomY)
{
	char _cBoxTile;
	for (int _iX = 1; _iX < (_iBottomX - _iTopX); ++_iX)
	{
		GotoXY(_iTopX + _iX, _iTopY);
			_cBoxTile = 205;
			std::cout << _cBoxTile;
			GotoXY(_iTopX + _iX, _iBottomY);
			std::cout << _cBoxTile;
			if (_iX < (_iBottomY - _iTopY)) {
				GotoXY(_iTopX, _iTopY + _iX);
				_cBoxTile = 186;
				std::cout << _cBoxTile;
				GotoXY(_iBottomX, _iTopY + _iX);
				_cBoxTile = 186;
				std::cout << _cBoxTile;
			}
	}

	GotoXY(_iTopX, _iTopY);
	_cBoxTile = 201;
	std::cout << _cBoxTile;

	GotoXY(_iBottomX, _iTopY);
	_cBoxTile = 187;
	std::cout << _cBoxTile;

	GotoXY(_iTopX, _iBottomY);
	_cBoxTile = 200;
	std::cout << _cBoxTile;

	GotoXY(_iBottomX, _iBottomY);
	_cBoxTile = 188;
	std::cout << _cBoxTile;
}



// Author: Jack Mair
// Input: Draws the Gameplay arena. Is called every 'gamephase' step after the players and attack objects have exectued their behaviour.
// Returns: void.
void CGameEngine::Draw()
{
	static int _ibackgroundcolour = 128;
	char _cIconHolder;

	DrawGrid(4, 4, 44, 20);
	DrawGrid(4, 4, 44, 20);

	GotoXY(14, 3);
	std::cout << "xX ARENA OF DEATH! Xx";

	if (m_pCurGameState == m_pstateGetInput)
	{
		SetConsoleTextAttribute(g_hConsole, 15);
		//m_pCurGameState->Step(this);
		GotoXY(4, 22);
		std::cout << "Player " << m_CommandOrder[m_pstateGetInput->GetI()] + 1;
		GotoXY(4, 23);
		std::cout << "Input Commands:";
		GotoXY(8, 25);
		std::cout << "[" << m_rgMoveList[0] <<"][" << m_rgMoveList[1]<< "]	["<<m_rgMoveList[2]<< "][" << m_rgMoveList[3]<< "]	[" << m_rgMoveList[4] << "][" << m_rgMoveList[5]<< "]";
		//Draws the move input list
		GotoXY(4, 27);
		std::cout << "Input Key:";
		GotoXY(4, 29);
		std::cout << "[1] Move:		[2] Rotate:		[3] Attack:";
		GotoXY(4, 31);
		std::cout << "[1] forward  1	[1] clockwise		[1] shoot";
		GotoXY(4, 32);
		std::cout << "[2] forward  2	[2] anti-clockwise	[2] push";
		GotoXY(4, 33);
		std::cout << "[3] forward  3	[3] flip		[3] mine";
		GotoXY(4, 34);
		std::cout << "[4] backward 1";
		for (int i = 0; i <= 5; ++i)
		{
			GotoXY(20, 29 + i);
			std::cout << ":";
			GotoXY(44, 29 + i);
			std::cout << ":";
		}
	}
	else
	{
		GotoXY(4, 23);
		std::cout << "Output Commands:";
		GotoXY(8, 25);
		std::cout << "[" << m_rgMoveList[0] << "][" << m_rgMoveList[1] << "]	[" << m_rgMoveList[2] << "][" << m_rgMoveList[3] << "]	[" << m_rgMoveList[4] << "][" << m_rgMoveList[5] << "]";
	}

	//Draws the icon key input list
	GotoXY(70, 4);
	std::cout << "Arena Key:";
	GotoXY(70, 6);
	std::cout << "    Empty Tile      Water";
	GotoXY(70, 8);
	std::cout << "    Pit             Mecha";
	GotoXY(70, 10);
	std::cout << "    Bullet          Mine";
	GotoXY(70, 12);

	GotoXY(71, 6);
	SetConsoleTextAttribute(g_hConsole, 128);
	std::cout << " ";

	GotoXY(87, 6);
	_cIconHolder = 126;
	SetConsoleTextAttribute(g_hConsole, 159);
	std::cout << _cIconHolder;
	
	GotoXY(71, 10);
	_cIconHolder = 249;
	SetConsoleTextAttribute(g_hConsole, 12);
	std::cout << _cIconHolder;

	GotoXY(87, 10);
	_cIconHolder = 15;
	SetConsoleTextAttribute(g_hConsole, 12);
	std::cout << _cIconHolder;
	
	GotoXY(71, 8);
	_cIconHolder = 220;
	SetConsoleTextAttribute(g_hConsole, 15);
	std::cout << _cIconHolder;

	GotoXY(87, 8);
	_cIconHolder = 30;
	std::cout << _cIconHolder;

	//Draws the player health UI
	if (m_Player1.GetMecha() != nullptr) 
	{
		GotoXY(54, 5);
		std::cout << "Player 1";
		GotoXY(54, 6);
		std::cout << "HP: " << m_PlayerList[0].GetMecha()->GetHealth();
		if (m_Player1.CheckDeath() != true) {
			SetConsoleTextAttribute(g_hConsole, (13));
		}
		GotoXY(52, 5);
		_cIconHolder = 30;
		std::cout << _cIconHolder;
		DrawFirstPlayer(m_Player1, 51, 5);
		SetConsoleTextAttribute(g_hConsole, 15);
	}
	if (m_Player2.GetMecha() != nullptr) 
	{
		GotoXY(54, 8);
		std::cout << "Player 2";
		GotoXY(54, 9);
		std::cout << "HP: " << m_PlayerList[1].GetMecha()->GetHealth();
		if (m_Player2.CheckDeath() != true) {
			SetConsoleTextAttribute(g_hConsole, (14));
		}
		GotoXY(52, 8);
		_cIconHolder = 30;
		std::cout << _cIconHolder;
		DrawFirstPlayer(m_Player2, 51, 8);
		SetConsoleTextAttribute(g_hConsole, 15);
	}
	if (m_Player3.GetMecha() != nullptr && m_PlayerList.size() >=3) 
	{
		GotoXY(54, 11);
		std::cout << "Player 3";
		GotoXY(54, 12);
		std::cout << "HP: " << m_PlayerList[2].GetMecha()->GetHealth();
		if (m_Player3.CheckDeath() != true) {
			SetConsoleTextAttribute(g_hConsole, (10));
		}
		GotoXY(52, 11);
		_cIconHolder = 30;
		std::cout << _cIconHolder;
		DrawFirstPlayer(m_Player3, 51, 11);

		SetConsoleTextAttribute(g_hConsole, 15);
	}
	if (m_Player4.GetMecha() != nullptr && m_PlayerList.size() == 4) 
	{
		GotoXY(54, 14);
		std::cout << "Player 4";
		GotoXY(54, 15);
		std::cout << "HP: " << m_PlayerList[3].GetMecha()->GetHealth();
		if (m_Player4.CheckDeath() != true) {
			SetConsoleTextAttribute(g_hConsole, (11));
		}
		GotoXY(52, 14);
		_cIconHolder = 30;
		std::cout << _cIconHolder;
		DrawFirstPlayer(m_Player4, 51, 14);

		SetConsoleTextAttribute(g_hConsole, 15);
	}
	
	//draws the arena
	for (int _iY = 0; _iY < 10; ++_iY)
	{
		GotoXY(10 + _iY, 7 + _iY);
		for (int _iX = 0; _iX < 10; ++_iX)
		{
			if (m_Level.GetTile(_iX, _iY).GetEnvironment() == WATER) {
				_ibackgroundcolour = 144;
			}
			else {
				_ibackgroundcolour = 128;
			}
			//draw an empty tile
			if (m_Level.GetTile(_iX, _iY).GetEnvironment() == FLOOR 
				&& m_Level.GetTile(_iX, _iY).GetMecha() == nullptr 
				&& m_Level.GetTile(_iX, _iY).GetMine() == nullptr
				&& m_Level.GetTile(_iX, _iY).GetBullet() == nullptr)
			{
				std::cout << " ";
				SetConsoleTextAttribute(g_hConsole, 15);
			}
			//draw mecha
			else if (m_Level.GetTile(_iX, _iY).GetMecha() != nullptr)
			{
				if (m_Level.GetTile(_iX, _iY).GetMecha()->getID() == 1)
				{
					SetConsoleTextAttribute(g_hConsole, (_ibackgroundcolour + 13));
				}
				else if (m_Level.GetTile(_iX, _iY).GetMecha()->getID() == 2)
				{
					SetConsoleTextAttribute(g_hConsole, (_ibackgroundcolour + 14));
				}
				else if (m_Level.GetTile(_iX, _iY).GetMecha()->getID() == 3)
				{
					SetConsoleTextAttribute(g_hConsole, (_ibackgroundcolour + 10));
				}
				else
				{
					SetConsoleTextAttribute(g_hConsole, (_ibackgroundcolour + 11));
				}

				char _cMechaImage;
				if (m_Level.GetTile(_iX, _iY).GetMecha()->GetDirection() == NORTH)
				{
					 _cMechaImage = 30;
				}
				if (m_Level.GetTile(_iX, _iY).GetMecha()->GetDirection() == EAST)
				{
					 _cMechaImage = 16;
				}
				if (m_Level.GetTile(_iX, _iY).GetMecha()->GetDirection() == SOUTH)
				{
					 _cMechaImage = 31;
				}
				if (m_Level.GetTile(_iX, _iY).GetMecha()->GetDirection() == WEST)
				{
					_cMechaImage = 17;
				}
				std::cout << _cMechaImage;
				SetConsoleTextAttribute(g_hConsole, 15);
				SetConsoleTextAttribute(g_hConsole, 128);
			}

			////draw bullet
			else if (m_Level.GetTile(_iX, _iY).GetBullet() != nullptr)
			{
				char _cBulletImage = 249;
				SetConsoleTextAttribute(g_hConsole, _ibackgroundcolour + 12);
				std::cout << _cBulletImage;
				SetConsoleTextAttribute(g_hConsole, 15);
			}
			//draw mine
			else if (m_Level.GetTile(_iX, _iY).GetMine() != nullptr)
			{
				if (m_Level.GetTile(_iX, _iY).GetEnvironment() == PIT)
				{
					m_Level.GetTile(_iX, _iY).SetMine(nullptr);
					m_Level.GetTile(_iX, _iY).GetMine()->bombBlown();
					char _cPitImage = 220;
					SetConsoleTextAttribute(g_hConsole, 15);
					std::cout << _cPitImage;
				}
				else
				{
					char _cMineImage = 15;
					SetConsoleTextAttribute(g_hConsole, _ibackgroundcolour + 12);
					std::cout << _cMineImage;
					m_Level.GetTile(_iX, _iY).GetMine()->ArmMine();
					SetConsoleTextAttribute(g_hConsole, 15);
				}
				
			}

			////draw water
			else if (m_Level.GetTile(_iX, _iY).GetEnvironment() == WATER)
			{
				char _cWaterImage = 126;
				SetConsoleTextAttribute(g_hConsole, 159);
				std::cout << _cWaterImage;
				SetConsoleTextAttribute(g_hConsole, 15);
			}
			////draw pit
			else if (m_Level.GetTile(_iX, _iY).GetEnvironment() == PIT)
			{
				char _cPitImage = 220;
				SetConsoleTextAttribute(g_hConsole, 15);
				std::cout << _cPitImage;
			}
			SetConsoleTextAttribute(g_hConsole, 15);
			std::cout << " ";
			SetConsoleTextAttribute(g_hConsole, 128);
		}
	}

	SetConsoleTextAttribute(g_hConsole, 15);
	GotoXY(m_iCursorPos, 25);
	
}

void CGameEngine::ChangeState(IGameState* _pState)
{
	if (m_pCurGameState != nullptr)
	{
		//std::cout << m_Player1.GetMecha()->m_posGridPosition.m_iX;

		m_pCurGameState->Cleanup();
		//delete m_pCurGameState;
	}

	m_pCurGameState = _pState;

	if (_pState != nullptr)
	{
		//std::cout << m_Player1.GetMecha()->m_posGridPosition.m_iX;

		_pState->Init();
	}
}

CBoard& CGameEngine::LoadBoard(int _LevelNum, int _playerCount) {

	std::ifstream LoadFile;

	///////////////////////////////////////////////////////////////////////////CHANGE BACK/////////////////////////////////////////////////////////////////////////////


	if (_LevelNum == 1) {
		//sets the players starting locations and facing direction

		m_PlayerList[0].GetMecha()->SetGridPosition({ 8, 7 });
		m_PlayerList[0].GetMecha()->SetMechaFacingDirect(NORTH);

		if (_playerCount != 2)
		{
			m_PlayerList[1].GetMecha()->SetGridPosition({ 2, 8 });
			m_PlayerList[1].GetMecha()->SetMechaFacingDirect(EAST);


			m_PlayerList[2].GetMecha()->SetGridPosition({ 7, 1 });
			m_PlayerList[2].GetMecha()->SetMechaFacingDirect(WEST);
		}
		else
		{
			m_PlayerList[1].GetMecha()->SetGridPosition({ 2, 8 });
			m_PlayerList[1].GetMecha()->SetMechaFacingDirect(EAST);
		}
		if (_playerCount == 4)
		{
			m_PlayerList[3].GetMecha()->SetGridPosition({ 1, 2 });
			m_PlayerList[3].GetMecha()->SetMechaFacingDirect(SOUTH);
		}
		//include code here load level 1 from txt file

		LoadFile.open("LevelOne.txt");
		if (LoadFile.is_open() == false)
		{
			std::cout << "Error opening file." << std::endl;
		}
	}
	else if (_LevelNum == 2) {
		//sets the players starting locations and facing direction

		m_PlayerList[0].GetMecha()->SetGridPosition({ 2, 2 });
		m_PlayerList[0].GetMecha()->SetMechaFacingDirect(SOUTH);

		if (_playerCount != 2)
		{
			m_PlayerList[1].GetMecha()->SetGridPosition({ 2, 7 });
			m_PlayerList[1].GetMecha()->SetMechaFacingDirect(EAST);

			m_PlayerList[2].GetMecha()->SetGridPosition({ 7, 2 });
			m_PlayerList[2].GetMecha()->SetMechaFacingDirect(WEST);
		}
		else
		{
			m_PlayerList[1].GetMecha()->SetGridPosition({ 7, 7 });
			m_PlayerList[1].GetMecha()->SetMechaFacingDirect(NORTH);
		}
		if (_playerCount == 4)
		{
			m_PlayerList[3].GetMecha()->SetGridPosition({ 7, 7 });
			m_PlayerList[3].GetMecha()->SetMechaFacingDirect(NORTH);
		}

		//include code here load level 2 from txt file

		LoadFile.open("LevelTwo.txt");
		if (LoadFile.is_open() == false)
		{
			std::cout << "Error opening file." << std::endl;
		}
	}
	else if (_LevelNum == 3) {
		//sets the players starting locations and facing direction

		m_PlayerList[0].GetMecha()->SetGridPosition({ 4, 6 });
		m_PlayerList[0].GetMecha()->SetMechaFacingDirect(NORTH);

		if (_playerCount != 2)
		{
			m_PlayerList[1].GetMecha()->SetGridPosition({ 5, 3 });
			m_PlayerList[1].GetMecha()->SetMechaFacingDirect(SOUTH);

			m_PlayerList[2].GetMecha()->SetGridPosition({ 6, 5 });
			m_PlayerList[2].GetMecha()->SetMechaFacingDirect(WEST);
		}
		else
		{
			m_PlayerList[1].GetMecha()->SetGridPosition({ 5, 4 });
			m_PlayerList[1].GetMecha()->SetMechaFacingDirect(SOUTH);
		}
		if (_playerCount == 4)
		{
			m_PlayerList[3].GetMecha()->SetGridPosition({ 3, 4 });
			m_PlayerList[3].GetMecha()->SetMechaFacingDirect(EAST);
		}

		//include code here load level 3 from txt file

		LoadFile.open("LevelThree.txt");
		if (LoadFile.is_open() == false)
		{
			std::cout << "Error opening file." << std::endl;
		}

	}
	else {
		//sets the players starting locations and facing direction

		m_PlayerList[0].GetMecha()->SetGridPosition({ 4, 7 });
		m_PlayerList[0].GetMecha()->SetMechaFacingDirect(NORTH);

		if (_playerCount != 2)
		{
			m_PlayerList[1].GetMecha()->SetGridPosition({ 5, 2 });
			m_PlayerList[1].GetMecha()->SetMechaFacingDirect(SOUTH);

			m_PlayerList[2].GetMecha()->SetGridPosition({ 7, 5 });
			m_PlayerList[2].GetMecha()->SetMechaFacingDirect(WEST);
		}
		else
		{
			m_PlayerList[1].GetMecha()->SetGridPosition({ 5, 2 });
			m_PlayerList[1].GetMecha()->SetMechaFacingDirect(SOUTH);
		}
		if (_playerCount == 4)
		{
			m_PlayerList[3].GetMecha()->SetGridPosition({ 2, 4 });
			m_PlayerList[3].GetMecha()->SetMechaFacingDirect(EAST);
		}

		//include code here load level 4 from txt file

		LoadFile.open("LevelFour.txt");
		if (LoadFile.is_open() == false)
		{
			std::cout << "Error opening file." << std::endl;
		}

	}

	int j = 0;

	for (std::string line; getline(LoadFile, line); j++)
	{
		for (int i = 0; i < 10; i++)
		{
			switch (line[i])
			{
			case 'p':
			{
				m_Level.GetTile(i, j).SetEnvironment(PIT);
				break;
			}
			case '0':
			{
				break;
			}
			case 'w':
			{
				m_Level.GetTile(i, j).SetEnvironment(WATER);

				break;
			}
			default:
			{
				break;
			}
			}
		}
	}

	LoadFile.close();

	return m_Level;
}

CBoard & CGameEngine::GetBoard()
{
	return m_Level;
}


std::vector<CPlayer>& CGameEngine::GetPlayerList()
{
	return m_PlayerList;
}

std::vector<CBullet*>& CGameEngine::GetBulletList()
{
	return m_vecpBulletList;
}


void CGameEngine::Run()
{
	// Size console window
	int iFontSize = 6;
	setFontSize(iFontSize);
	HANDLE hHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	set_console_size(hHandle, 316, 117);

	// Set font size
	//int iFontSize = 6;
	//setFontSize(iFontSize);
	GotoXY(118, 17);
	std::cout << "                            .###'.                                               ";
	GotoXY(118, 18);
	std::cout << "                         .'#      #+',                                         ";
	GotoXY(118, 19);
	std::cout << "                      ,#;    .'#+.    ,++':`									 ";
	GotoXY(118, 20);
	std::cout << "                      #;   '+         .'#',#+.`.;##';                          ";
	GotoXY(118, 21);
	std::cout << "                     #`   +,             ;##.      ###:                        ";
	GotoXY(118, 22);
	std::cout << "                    ::   ;:                `#+`   ',  '#+.                     ";
	GotoXY(118, 23);
	std::cout << "                    +    #                   .#'  `++`  `#+`                   ";
	GotoXY(118, 24);
	std::cout << "                    #    #                     ;#`  `#+:+###;                  ";
	GotoXY(118, 25);
	std::cout << "                    +    #                      `#;   `;`   .#;                ";
	GotoXY(118, 26);
	std::cout << "               ,,   '`   #                        ++          '#`              ";
	GotoXY(118, 27);
	std::cout << "            '+#++++,'.   :+                        '+           #:             ";
	GotoXY(118, 28);
	std::cout << "          '#;`    ,++'`   ;#`                       '#           ;+            ";
	GotoXY(118, 29);
	std::cout << "         ;#`  ,`    .;+#,  `++`                      +;       :####;           ";
	GotoXY(118, 30);
	std::cout << "        `#  `#;+,      `;#:` .++.                     #.          `+'          ";
	GotoXY(118, 31);
	std::cout << "        +, `#`` '.        :++` `;#'.                   #        `'. ';         ";
	GotoXY(118, 32);
	std::cout << "       `# `#`.''.#          `'+`  .'#;                 ;:        ,+#:#         ";
	GotoXY(118, 33);
	std::cout << "       ;, +'`;:++`        `,,:.+`    :#;                #          `+#,        ";
	GotoXY(118, 34);
	std::cout << "       +``+`'+.#`       `+#;,:+#:      :#;              ;;           ;#        ";
	GotoXY(118, 35);
	std::cout << "       # +;#..:,       '#:     .',       ;+              #    '+,   ,+.#,      ";
	GotoXY(118, 36);
	std::cout << "       # #+,;'+      `'#.  .    ,#        .#             #     `;#' #  #'#:    ";
	GotoXY(118, 37);
	std::cout << "       + .#,;;`      '+    ,#:   +`        .+            '        .## +'  ##,  ";
	GotoXY(118, 38);
	std::cout << "       :.  +#+      :+       ;#` ;,         :;           :,   ;+    .'.  #.`#  ";
	GotoXY(118, 39);
	std::cout << "        ++          +,  ,#`    #`,,          #           `'    ,#,   ;+`:.  #  ";
	GotoXY(118, 40);
	std::cout << "         .#;       `#     #+  +##`#,         ,,           +      ;#  .+:#+;#:  ";
	GotoXY(118, 41);
	std::cout << "           ++`     ::      :#,; :, +,        `;          `; `     ;#,.         ";
	GotoXY(118, 42);
	std::cout << "            :+'    '`       .#. +`  ++        +          #` `+`  +'.#          ";
	GotoXY(118, 43);
	std::cout << "              ++   '       ';`##+'`#::.       +,     `,#+##,.,#,,;  +.         ";
	GotoXY(118, 44);
	std::cout << "               '+` '        :#..+:#+`'`   :###.;#####+: #  #,, '#;,,+          ";
	GotoXY(118, 45);
	std::cout << "                .+.;,         '#` `++,   ':   '`        :  ;     .;,           ";
	GotoXY(118, 46);
	std::cout << "                  ''#          .#;       +     +   ,'+; '  #                   ";
	GotoXY(118, 47);
	std::cout << "                   :#;   `#`  `#.''     `.     #:++;.`++###:                   ";
	GotoXY(118, 48);
	std::cout << "                   `#++:` ;#; ;. .#      '    ,+,     ;:.                      ";
	GotoXY(118, 49);
	std::cout << "                   ': ,###, ;+#  ;;  '+` .+,,:#       `+                       ";
	GotoXY(118, 50);
	std::cout << "                   #         .#.''   ;;#,`'#;,         ''`                     ";
	GotoXY(118, 51);
	std::cout << "                  '.          `;:   ;;  ,;..'           .#.,,                  ";
	GotoXY(118, 52);
	std::cout << "                 :;              ,`;;       ;+`       `'###+#+`                ";
	GotoXY(118, 53);
	std::cout << "                +.             .###+         `#+    `+#,     `#.               ";
	GotoXY(118, 54);
	std::cout << "               +`  ;++#+;     .##.#            .#, '#.        .+               ";
	GotoXY(118, 55);
	std::cout << "              `+##+,`  .##    ,++',              +++           #               ";
	GotoXY(118, 56);
	std::cout << "              +#.        '#    ';:               .#            #               ";
	GotoXY(118, 57);
	std::cout << "             :#           +.   :'                '.            #               ";
	GotoXY(118, 58);
	std::cout << "             +,           .+  .+                 #             #               ";
	GotoXY(118, 59);
	std::cout << "             #             #  #                 .+             +               ";
	GotoXY(118, 60);
	std::cout << "            `#             #  +                 ;,            ,:               ";
	GotoXY(118, 61);
	std::cout << "            ,+             +`.,                 +`            ;.               ";
	GotoXY(118, 62);
	std::cout << "            '+             ':+                  #             +                ";
	GotoXY(118, 63);
	std::cout << "            ++             ;;+                  #            `#                ";
	GotoXY(118, 64);
	std::cout << "            +'             :':                 .'           '#,+               ";
	GotoXY(118, 65);
	std::cout << "            +'             :#                  :,       `,+#:  ,'              ";
	GotoXY(118, 66);
	std::cout << "            +:             '+                  +#+++++###;`     +              ";
	GotoXY(118, 67);
	std::cout << "            +,             '.                  +`    '+   ;#+`  ;.             ";
	GotoXY(118, 68);
	std::cout << "            '.             +.                  #     #:,  # .#.`#              ";
	GotoXY(118, 69);
	std::cout << "            ;:             '.                  #    ;'`+  #   ++  `            ";
	GotoXY(118, 70);
	std::cout << "            .'             +`                  `#++#+  #`.+                    ";
	GotoXY(118, 71);
	std::cout << "           `'#            ;#`                    ``     ++.                    ";
	GotoXY(118, 72);
	std::cout << "         :##:;#',```   `;#;+`                                                  ";
	GotoXY(118, 73);
	std::cout << "       :#;`    ,'++##++',  #                                                   ";
	GotoXY(118, 74);
	std::cout << "      ;+   ,+#:           ;'                                                   ";
	GotoXY(118, 75);
	std::cout << "     `#  .++` #    '#    `#                                                    ";
	GotoXY(118, 76);
	std::cout << "     `+:+#;   #   ,+#    +,                                                    ";
	GotoXY(118, 78);
	std::cout << "      ;;.    `+  `#`#  :#:                                                     ";
	GotoXY(118, 79);
	std::cout << "             ': `#, +;++`                                                      ";
	GotoXY(118, 80);
	std::cout << "             +:'#.   ,.                                                        ";
	GotoXY(118, 81);
	std::cout << "             `:.                                                               ";

	GotoXY(55, 87);
	std::cout << "   ??    ??    ???    ??    ???????????      ????????? ???????    ??      ???     ???   ???  ? ?????????       ??          ?????????    ?????????     ???             ??    ??     ????????     ?????????    ?????????  ";
	GotoXY(55, 88);
	std::cout << "   ???    ???   ???    ??? ???????????????   ???    ??? ????????? ???  ??????????? ???   ???   ???    ???      ???         ???    ???   ???    ??? ???????????        ???    ???   ???    ???   ???    ???   ???    ??? ";
	GotoXY(55, 89);
	std::cout << "  ???    ???   ???    ??? ???   ???   ???   ???    ??? ???   ??? ????    ???????? ?????????   ???    ??       ???         ???    ???   ???    ??     ????????        ???    ???   ???    ???   ???    ???   ???    ??   ";
	GotoXY(55, 90);
	std::cout << " ????????????? ???    ??? ???   ???   ???   ???    ??? ???   ??? ????     ???   ? ?????????   ???             ???         ???    ???   ???            ???   ?       ????????????? ???    ???   ???    ???  ???????      ";
	GotoXY(55, 91);
	std::cout << "?????????????  ???    ??? ???   ???   ??? ???????????? ???   ??? ????     ???           ??? ????????????      ???       ???????????? ????????????     ???          ?????????????  ???    ??? ???????????  ????????      ";
	GotoXY(55, 92);
	std::cout << "  ???    ???   ???    ??? ???   ???   ???   ???    ??? ???   ??? ???      ???     ??    ???          ???      ???         ???    ???          ???     ???            ???    ???   ???    ???   ???          ???    ??   ";
	GotoXY(55, 93);
	std::cout << "   ???    ???   ???    ??? ???   ???   ???   ???    ??? ???   ??? ???      ???     ???   ???    ??    ???      ????    ?   ???    ???    ??    ???     ???            ???    ???   ???    ???   ???          ???    ??? ";
	GotoXY(55, 94);
	std::cout << "  ???    ??    ?????????   ??   ???   ??    ???    ??   ??   ??  ??      ??????    ???????   ??????????       ?????????   ???    ??   ??????????     ??????          ???    ??     ????????   ??????        ??????????  ";
	GotoXY(55, 95);
	std::cout << "                                                                                                              ?                                                                                                         ";

	_getch();
   
	
	system("CLS");
	// Set font size
	set_console_size(hHandle, 114, 40);
	iFontSize = 18;
	setFontSize(iFontSize);

	GotoXY(4, 6);
	std::cout << "After scavenging, stealing, and constructing your Warrior Mechas you have entered the Great City ";
	GotoXY(4, 7);
	std::cout << "in search for salvation from the dangerous and chaotic world you have grown up in. From here you";
	GotoXY(4, 8);
	std::cout << "have discovered one of the many mecha arenas in the city; offering fame, glory, and cash prizes";
	GotoXY(4, 9);
	std::cout << "for anyone who enters and survives.";
	GotoXY(4, 11);
	std::cout << "For the amusement of the blood crazed crowds, and with an arsenal of weapons and dirty tricks, ";
	GotoXY(4, 12);
	std::cout << "you must battle against each other in the Arena of Death! Only one may survive!";
	GotoXY(4, 14);
	std::cout << "Welcome pilots, to:...";

	_getch();

	while (true) {
		//Draw the Start Screen.
		system("CLS");
		GotoXY(4, 4);
		std::cout << "   _____               .__                _____                .__        ";
		GotoXY(4, 5);
		std::cout << "  /     \\   ____  ____ |  |__ _____      /     \\ _____    ____ |__|____   ";
		GotoXY(4, 6);
		std::cout << " /  \\ /  \\_/ __ \\/ ___\\|  |  \\\\__  \\    /  \\ /  \\\\__  \\  /    \\|  \\__  \\  ";
		GotoXY(4, 7);
		std::cout << "/    Y    \\  ___|  \\___|   Y  \\/ __ \\_ /    Y    \\/ __ \\|   |  \\  |/ __ \\_";
		GotoXY(4, 8);
		std::cout << "\\____|__  /\\___  >___  >___|  (____  / \\____|__  (____  /___|  /__(____  /";
		GotoXY(4, 9);
		std::cout << "   _____\\/     \\/    \\/     \\/   __\\/          \\/     \\_____ \\/        \\/	.__";
		GotoXY(4, 10);
		std::cout << "  /     \\   ____   ____   ______/  |_  ___________    /     \\ _____    _____|  |__   ___________  ______";
		GotoXY(4, 11);
		std::cout << " /  \\ /  \\ /  _ \\ /    \\ /  ___|   __\\/ __ \\_  __ \\  /  \\ /  \\\\__  \\  /  ___/  |  \\_/ __ \\_  __ \\/  ___/";
		GotoXY(4, 12);
		std::cout << "/    Y    (  <_> )   |  \\\\___ \\ |  | \\  ___/|  | \\/ /    Y    \\/ __ \\_\\___ \\|   Y  \\  ___/|  | \\/\\___ \\ ";
		GotoXY(4, 13);
		std::cout << "\\____|__  /\\____/|___|  /____  >|__|  \\___  >__|    \\____|__  (____  /____  >___|  /\\___  >__|  /____  >";
		GotoXY(4, 14);
		std::cout << "	    \\/            \\/     \\/           \\/                \\/     \\/     \\/     \\/     \\/           \\/ ";

		GotoXY(34, 16);
		std::cout << "xX THE BADASS BULLET BRAWLER Xx";
		GotoXY(4, 22);
		std::cout << "Input a command: [ ]";
		GotoXY(4, 24);
		std::cout << "[1] Play";
		GotoXY(4, 25);
		std::cout << "[2] Controls";
		GotoXY(4, 26);
		std::cout << "[3] Quit";
		GotoXY(69, 34);
		std::cout << "Created by: Lance Chaney, Madeleine Day,";
		GotoXY(69, 35);
		std::cout << "		Jack Mair, Sebastian Tengdahl";
		GotoXY(69, 37);
		std::cout << "    Mecha Mania Monster Mashers (c) 2017";
		GotoXY(22, 22);

		int _iMenuInput = inputValidator(1, 3, "Invalid Input.", 22, 22, 4, 23);

		//Go to the gameplay
		if (_iMenuInput == 1)
		{
			//Player Count screen
			DrawGrid(30, 16, 72, 27);
			GotoXY(34, 18);
			std::cout << "How many players? [ ]";
			GotoXY(36, 21);
			std::cout << "[2] 2 Pilots";
			GotoXY(36, 22);
			std::cout << "[3] 3 Pilots";
			GotoXY(36, 23);
			std::cout << "[4] 4 Pilots";
			GotoXY(36, 25);
			std::cout << "[5] back";
			GotoXY(53, 18);

			int _iPlayerCount = inputValidator(2, 5, "Invalid Input.", 53, 18, 34, 19);

			// Initialize game
			if (_iPlayerCount != 5)
			{
				CGameEngine gameEngine(_iPlayerCount);

				


				system("CLS");
				while (true)
				{
					gameEngine.Draw();
					gameEngine.Step();

					if (gameEngine.playerAliveCount <= 1 && gameEngine.inGetState == true)
					{
						break;
					}
				}
				system("CLS");
				
				if (gameEngine.m_pWinner != nullptr) // A player won
				{
					int i_WinnerColour;
					int i_LoserColour1;
					int i_LoserColour2;
					int i_LoserColour3;
					if (gameEngine.m_pWinner->GetMecha()->getID() == 1)
					{
						i_WinnerColour = 13;
						i_LoserColour1 = 14;
						i_LoserColour2 = 10;
						i_LoserColour3 = 11;
					}
					else if (gameEngine.m_pWinner->GetMecha()->getID() == 2)
					{
						i_LoserColour1 = 13;
						i_WinnerColour = 14;
						i_LoserColour2 = 10;
						i_LoserColour3 = 11;
					}
					else if (gameEngine.m_pWinner->GetMecha()->getID() == 3)
					{
						i_LoserColour1 = 13;
						i_LoserColour2 = 14;
						i_WinnerColour = 10;
						i_LoserColour3 = 11;
					}
					else if (gameEngine.m_pWinner->GetMecha()->getID() == 4)
					{
						i_LoserColour1 = 13;
						i_LoserColour2 = 14;
						i_LoserColour3 = 10;
						i_WinnerColour = 11;
					}
					
					system("CLS");
					char _cBulletImage;
					
					_cBulletImage = 249;
					SetConsoleTextAttribute(g_hConsole, 140);
					GotoXY(48, 12);
					std::cout << _cBulletImage;
					GotoXY(52, 12);
					std::cout << _cBulletImage;
					GotoXY(56, 12);
					std::cout << _cBulletImage;
					GotoXY(46, 13);
					std::cout << _cBulletImage;
					GotoXY(50, 13);
					std::cout << _cBulletImage;
					GotoXY(54, 13);
					std::cout << _cBulletImage;
					GotoXY(58, 13);
					std::cout << _cBulletImage;
					GotoXY(48, 14);
					_cBulletImage = 31;
					SetConsoleTextAttribute(g_hConsole, i_LoserColour1);
					std::cout << _cBulletImage;
				
					if (_iPlayerCount > 2) {
						GotoXY(52, 14);
						SetConsoleTextAttribute(g_hConsole, i_LoserColour2);
						std::cout << _cBulletImage;
					}
					if (_iPlayerCount > 3) {
						GotoXY(56, 14);
						SetConsoleTextAttribute(g_hConsole, i_LoserColour3);
						std::cout << _cBulletImage;
					}

					if (gameEngine.m_pWinner->bDead == false) //Winning Player Survived
					{
						GotoXY(52, 10);
						_cBulletImage = 30;
						SetConsoleTextAttribute(g_hConsole, i_WinnerColour);
						std::cout << _cBulletImage;
						SetConsoleTextAttribute(g_hConsole, 15);
						GotoXY(38, 16);
						std::cout << "Player " << gameEngine.m_pWinner->GetMecha()->getID() << " is the W I N N E R!";
						GotoXY(30, 18);
						std::cout << "You have won your place in the eternal paradise";
						GotoXY(37, 19);
						std::cout << "of the Valhalla Apartment Complex.";
					}

					if (gameEngine.m_pWinner->bDead == true) // Winning player died before the end of the round
					{
						GotoXY(52, 10);
						_cBulletImage = 31;
						SetConsoleTextAttribute(g_hConsole, i_WinnerColour);
						std::cout << _cBulletImage;
						SetConsoleTextAttribute(g_hConsole, 15);
						GotoXY(34, 16);
						std::cout << "Player " << gameEngine.m_pWinner->GetMecha()->getID() << " was going to win, but then D I E D! SAD!";
					}
				}
				else
				{
					GotoXY(34, 15);
					std::cout << "Everyone died.";
					GotoXY(34, 16);
					std::cout << "GAME OVER LOSERS" << std::endl; // NO ONE DETECTED AS THE WINNER
				}

				GotoXY(6, 29);
				std::cout << "Press any key to refuse your reward and fight in the xX Arena of Death Xx once more...";
				GotoXY(69, 34);
				std::cout << "Created by: Lance Chaney, Madeleine Day,";
				GotoXY(69, 35);
				std::cout << "		Jack Mair, Sebastian Tengdahl";
				GotoXY(69, 37);
				std::cout << "    Mecha Mania Monster Mashers (c) 2017";

				_getch();

			}
			else
			{
				// Go back to home screen
			}
		}
		//Go to the controlscreen
		else if (_iMenuInput == 2)
		{
			system("CLS");
			GotoXY(4, 4);
			std::cout << "Overview:";
			GotoXY(4, 6);
			std::cout << "Mecha Mania is a turn based fighting game for 2-4 players. Each player controls their Mecha";
			GotoXY(4, 7);
			std::cout << "by taking turns to secretly input a set of three commands. They then watch all the commands";
			GotoXY(4, 8);
			std::cout << "unfold one at a time. Players battle one another with their Mecha in tightly spaced arenas";
			GotoXY(4, 9);
			std::cout << "until only one survives.";
			GotoXY(4, 11);
			std::cout << "Inputting Commands:";
			GotoXY(4, 13);
			std::cout << "The game is divided into two phases: input phase, and action phase. During the input phase,";
			GotoXY(4, 14);
			std::cout << "players take turns to input their commands. They do this by inputting 2 numbers, 3 times.";
			GotoXY(4, 15);
			std::cout << "Each pair of numbers represents 1 action.";
			GotoXY(4, 17);
			std::cout << "The first number represents the type of action they want to perfrom.";
			GotoXY(4, 18);
			std::cout << "This number can be one of the following: [1] Move [2] Rotate [3] Attack.";
			GotoXY(4, 20);
			std::cout << "The second number represents different ways this action can be performed.";
			GotoXY(4, 22);
			std::cout << "If Move was chosen as the 1st number, the 2nd number represents how far you wish to move:";
			GotoXY(4, 23);
			std::cout << "[1] 1 Space	[2] 2 Spaces	[3] 3 Spaces	[4] -1 Spaces";
			GotoXY(4, 25);
			std::cout << "If Rotate was chosen as the 1st number, the 2nd number represents how the degree of rotation:";
			GotoXY(4, 26);
			std::cout << "[1] Clockwise 90 degrees	[2] Anti-Clockwise 90 degrees	[3] 180 degrees";
			GotoXY(4, 28);
			std::cout << "If Attack was chosen as the 1st number, the 2nd number represents how you wish to attack:";
			GotoXY(4, 29);
			std::cout << "[1] Shoot a bullet	[2] Shoot a push attack	[3] Place a mine";
			GotoXY(4, 31);
			std::cout << "A bullet travels 1 space each phase and does 1 damage. Push instantly moves the first object";
			GotoXY(4, 32);
			std::cout << "infront of the Mecha 2 squares. A mine does 2 damage to any Mecha that stands on it.";
			GotoXY(4, 34);
			std::cout << "There are 2 enviromental hazards within the arena, water and pits:";
			GotoXY(4, 35);
			std::cout << "Water deals 1 damage to you when you enter it and 1 at the start of every turn you remain in it.";
			GotoXY(4, 36);
			std::cout << "A pit will instantly kill you if you walk on it, be careful!";
			_getch();
		}
		//Go to the confirm quit screen
		else if (_iMenuInput == 3)
		{
			DrawGrid(30, 16, 72, 25);
			GotoXY(34, 18);
			std::cout << "Are you sure you wish to quit?";
			GotoXY(34, 20);
			std::cout << "Input: [ ]";
			GotoXY(36, 22);
			std::cout << "Yes: [1]";
			GotoXY(36, 23);
			std::cout << " No: [2]";
			GotoXY(42, 20);
			int _QuitConfirm = inputValidator(1, 2, "Invalid Input.", 42, 20, 34, 19);
			if (_QuitConfirm == 1)
			{
				break;
			}
		}
	}

}

void CGameEngine::SetNewFirstPlayer()
{
	int iTemp = m_CommandOrder.front();

	do
	{
		m_CommandOrder.erase(m_CommandOrder.begin());
		m_CommandOrder.push_back(iTemp);
		iTemp = m_CommandOrder.front();

	} while (m_PlayerList[iTemp].bDead == true);

	
}

void CGameEngine::DrawFirstPlayer(CPlayer _Player, int _iX, int _iY)
{
	GotoXY(_iX, _iY);
	SetConsoleTextAttribute(g_hConsole, 12);
	if (m_CommandOrder.front()+1 == _Player.GetMecha()->getID())
	{
		
		std::cout << "*";
	}
	else
	{
		std::cout << " ";
	}
}

bool CGameEngine::BulletCollisionTest()
{
	bool bCollision = false;

	// Do bullet-bullet and bullet-mecha collision check
	for (auto it = m_vecpBulletList.begin(); it != m_vecpBulletList.end(); ++it)
	{
		CBullet* pBullet = *it;
		CTile& rTile = GetBoard().GetTile(pBullet->GetPosition());

		if (rTile.GetBulletCount() > 1)
		{
			bCollision = true;
			DestroyBullet(pBullet);
		}

		if (rTile.GetMecha() != nullptr)
		{
			bCollision = true;
			DestroyBullet(pBullet);

			rTile.GetMecha()->ChangeHealth(-pBullet->GetDamage());

			if (rTile.GetMecha()->GetHealth() <= 0)
			{
				ActionText('B', rTile.GetMecha(), true);

			}
			else
			{
				ActionText('B', rTile.GetMecha(), false);

			}
		}
	}

	return bCollision;
}

CBullet* CGameEngine::SpawnBullet(const TPosition& _posBoardPos, EDIRECTION _eMovingDir)
{
	// Check we are spawning at a valid position
	if (!m_Level.IsValidPos(_posBoardPos))
	{
		return nullptr;
	}
	else
	{
		// Check if the tile already has a bullet on it (both bullets should get destroyed in this case)
		CTile& tile = m_Level.GetTile(_posBoardPos);
		if (tile.GetBullet() != nullptr)
		{
			DestroyBullet(tile.GetBullet());

			return nullptr;
		}
		else
		{
			// Create the bullet at the end of the bullet list
			m_vecpBulletList.push_back(new CBullet(&m_Level, *this, _posBoardPos, _eMovingDir));

			// Add the bullet to the board at the correct location
			CBullet* pBullet = m_vecpBulletList.back();
			tile.AddBullet(pBullet);

			return pBullet;
		}
	}
}

void CGameEngine::DestroyBullet(CBullet * pBullet)
{
	// Set game engine state to destroy bullets at a later date
	m_bBulletsToDestroy = true;

	// Set bullets state to destroyed, game engine will do actual cleanup later
	pBullet->SetDestroyed();
}

void CGameEngine::ActuallyDestroyBullets()
{
	// Conditionally remove bullets, on the condition that they are in a destroyed state
	m_vecpBulletList.erase(std::remove_if(
		m_vecpBulletList.begin(), m_vecpBulletList.end(),
		[&](const CBullet* pBullet)
	{
		if (pBullet->IsDestroyed())
		{
			// Remove from board
			m_Level.GetTile(pBullet->GetPosition()).RemoveBullet(pBullet);

			// Delete memory
			delete pBullet;

			// Tell erase function to remove from list
			return true;
		}
		else
		{
			return false;
		}
	}
	), m_vecpBulletList.end());

	m_bBulletsToDestroy = false;
}

ExecutingCMDState* CGameEngine::GetExecutingState()
{
	return m_pstateExecuting;
}

CGettingPlayerMovesState* CGameEngine::GetGettingInputState()
{
	return m_pstateGetInput;
}

CMovingBulletsState* CGameEngine::GetMovBulletState()
{
	return m_pstateMovBullet;
}

void CGameEngine::SetMoveList(int _iNum, char _cOut)
{
	m_rgMoveList[_iNum] = _cOut;
	switch (_iNum)
	{
	case 0:
	{
		m_iCursorPos = 12;
		break;
	}
	case 1:
	{
		m_iCursorPos = 17;
		break;
	}
	case 2:
	{
		m_iCursorPos = 20;

		//GotoXY(16, 25);
		break;
	}
	case 3:
	{
		m_iCursorPos = 25;

		//GotoXY(19, 25);
		break;
	}
	case 4:
	{
		m_iCursorPos = 28;

		//GotoXY(25, 25);
		break;
	}
	case 5:
	{
		m_iCursorPos = 9;

		//GotoXY(28, 25);
		break;
	}
	}
}

void CGameEngine::ResetMoveList()
{
	for (int i = 0; i < 6; i++)
	{
		m_rgMoveList[i] = ' ';
	}

	if (m_pCurGameState == m_pstateExecuting)
	{
		for (int i = 0; i < m_PlayerList.size(); i++)
		{
 			m_PlayerList[i].ResetOutMoves();
		}
	}
}

void CGameEngine::ActionText(char _cAction, CMecha* _pMecha, bool _bDied)
{
	std::string strOutputText;

	int _iPlayer = _pMecha->getID();


	if (_pMecha->CheckDeath() == false)
	{
		switch (_cAction)
		{
		case 'P': // PIT
		{
			//GotoXY(9, 26);
			strOutputText = "Player " + std::to_string(_iPlayer) + " fell down a pit and died!";
			break;
		}
		case 'W': // WATER
		{
			//GotoXY(9, 26);
			strOutputText = "Player " + std::to_string(_iPlayer) + " took 1 damage from water";
			if (_bDied == true)
			{
				strOutputText += " and died!";
			}
			else
			{
				strOutputText += "!";
			}
			break;
		}
		case 'M': // MINE
		{
			//GotoXY(9, 26);
			strOutputText = "Player " + std::to_string(_iPlayer) + " took 2 damage from a mine";
			if (_bDied == true)
			{
				strOutputText += " and died!";
			}
			else
			{
				strOutputText += "!";
			}
			break;
		}
		case 'B': // BULLET
		{
			//GotoXY(9, 26);
			strOutputText = "Player " + std::to_string(_iPlayer) + " took 1 damage from a bullet";
			if (_bDied == true)
			{
				strOutputText += " and died!";
			}
			else
			{
				strOutputText += "!";
			}
			break;
		}
		case 'S': // SHOVE (push)
		{
			//GotoXY(9, 26);
			strOutputText = "Player " + std::to_string(_iPlayer) + " was pushed!";
			break;
		}
		default:
			break;

		}

		m_vecBattleActionText.push_back(strOutputText);
	}
	else
	{
		// Their death text was already displayed.
	}
	
}

std::vector<std::string>& CGameEngine::GetBattleActionText()
{
	return m_vecBattleActionText;
}

void CGameEngine::ResetBattleActionText()
{
	while(m_vecBattleActionText.empty() != true)
	{
		m_vecBattleActionText.pop_back();
	}

}

void CGameEngine::PrintBattleActionText()
{
	SetConsoleTextAttribute(g_hConsole, 8);

	for (int i = 0; i < m_vecBattleActionText.size(); i++)
	{
		
		if (i > 10)
		{
			GotoXY(40, 16 + i);
		}
		else
		{
			GotoXY(4, 27 + i);

		}
		std::cout << m_vecBattleActionText.at(i);

	}

	SetConsoleTextAttribute(g_hConsole, 15);

}
