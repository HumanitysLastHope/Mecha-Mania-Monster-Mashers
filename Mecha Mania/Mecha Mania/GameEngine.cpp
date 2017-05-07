#include "GameEngine.h"
#include "GameState.h"
#include "GettingPlayerMovesState.h"


CGameEngine::CGameEngine() :
	m_Player1({0,0}, NORTH, &m_Level),
	m_Player2({ 0,0 }, NORTH, &m_Level),
	m_Player3({ 0,0 }, NORTH, &m_Level),
	m_Player4({ 0,0 }, NORTH, &m_Level)
{
	ChangeState(new CGettingPlayerMovesState);
}


CGameEngine::~CGameEngine()
{
	delete m_pCurGameState;
}

void CGameEngine::Step()
{
	m_pCurGameState->Step(this);
}

void CGameEngine::Draw()
{
	LoadBoard(1);
	//draws the arena
	for (int _iY = 0; _iY < 10; ++_iY)
	{
		for (int _iX = 0; _iX < 10; ++_iX)
		{
			//draw an empty tile
			if (m_Level.GetTile(_iX, _iY).GetEnvironment() == FLOOR && m_Level.GetTile(_iX, _iY).GetMecha() == nullptr)
			{
				char _cEmptyTile = 176;
				std::cout << " " << _cEmptyTile;
			}
			//draw mecha
			if (m_Level.GetTile(_iX, _iY).GetMecha() != nullptr)
			{
				char _cMechaImage = 16;
				std::cout << " " << _cMechaImage;
			}
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
	m_pCurGameState->Step(this);
}

void CGameEngine::ChangeState(IGameState* _pState)
{
	if (m_pCurGameState != nullptr)
	{
		m_pCurGameState->Cleanup();
		delete m_pCurGameState;
	}

	m_pCurGameState = _pState;

	if (_pState != nullptr)
	{
		_pState->Init();
	}
}

CBoard& CGameEngine::LoadBoard(int _LevelNum) {
	if (_LevelNum == 1) {
		//sets the players starting locations and facing direction
		m_Player1.GetMecha()->SetGridPosition({ 1, 1 });
		m_Player1.GetMecha()->SetMechaFacingDirect(EAST);

		m_Player2.GetMecha()->SetGridPosition({ 1, 8 });
		m_Player2.GetMecha()->SetMechaFacingDirect(SOUTH);

		m_Player3.GetMecha()->SetGridPosition({ 8, 1 });
		m_Player3.GetMecha()->SetMechaFacingDirect(NORTH);

		m_Player4.GetMecha()->SetGridPosition({ 8, 8 });
		m_Player4.GetMecha()->SetMechaFacingDirect(WEST);

		//include code here load level 1 from txt file
		return m_Level;
	}
	if (_LevelNum == 2) {
		//sets the players starting locations and facing direction
		m_Player1.GetMecha()->SetGridPosition({ 1, 1 });
		m_Player1.GetMecha()->SetMechaFacingDirect(EAST);

		m_Player2.GetMecha()->SetGridPosition({ 1, 8 });
		m_Player2.GetMecha()->SetMechaFacingDirect(SOUTH);

		m_Player3.GetMecha()->SetGridPosition({ 8, 1 });
		m_Player3.GetMecha()->SetMechaFacingDirect(NORTH);

		m_Player4.GetMecha()->SetGridPosition({ 8, 8 });
		m_Player4.GetMecha()->SetMechaFacingDirect(WEST);

		//include code here load level 2 from txt file

		return m_Level;
	}
	if (_LevelNum == 3) {
		//sets the players starting locations and facing direction
		m_Player1.GetMecha()->SetGridPosition({ 1, 1 });
		m_Player1.GetMecha()->SetMechaFacingDirect(EAST);

		m_Player2.GetMecha()->SetGridPosition({ 1, 8 });
		m_Player2.GetMecha()->SetMechaFacingDirect(SOUTH);

		m_Player3.GetMecha()->SetGridPosition({ 8, 1 });
		m_Player3.GetMecha()->SetMechaFacingDirect(NORTH);

		m_Player4.GetMecha()->SetGridPosition({ 8, 8 });
		m_Player4.GetMecha()->SetMechaFacingDirect(WEST);

		//include code here load level 3 from txt file

		return m_Level;
	}
	else {
		//sets the players starting locations and facing direction
		m_Player1.GetMecha()->SetGridPosition({ 1, 1 });
		m_Player1.GetMecha()->SetMechaFacingDirect(EAST);

		m_Player2.GetMecha()->SetGridPosition({ 1, 8 });
		m_Player2.GetMecha()->SetMechaFacingDirect(SOUTH);

		m_Player3.GetMecha()->SetGridPosition({ 8, 1 });
		m_Player3.GetMecha()->SetMechaFacingDirect(NORTH);

		m_Player4.GetMecha()->SetGridPosition({ 8, 8 });
		m_Player4.GetMecha()->SetMechaFacingDirect(WEST);

		//include code here load level 4 from txt file

		return m_Level;
	}
}


std::vector<CPlayer>& CGameEngine::GetPlayerList()
{
	return m_PlayerList;
}

void CGameEngine::Run()
{
	CGameEngine gameEngine;

	gameEngine.Draw();
	_getch();
}