#include "GameEngine.h"
#include "GameState.h"
#include "GettingPlayerMovesState.h"


CGameEngine::CGameEngine()
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
	//draws the arena
	for (int _iY = 0; _iY < 10; ++_iY)
	{
		for (int _iX = 0; _iX < 10; ++_iX)
		{
			//draw an empty tile
			if (_pLevel.GetTile(_iX, _iY).GetEnvironment() == FLOOR && _pLevel.GetTile(0, 0).GetMecha() == NULL)
			{
				char _cEmptyTile = 176;
				std::cout << " " << _cEmptyTile;
			}
			//draw mecha
			if (_pLevel.GetTile(_iX, _iY).GetMecha() != NULL)
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
	if (_LevelNum = 1) {
		//include code here load level 1 from txt file
		return _pLevel;
	}
	if (_LevelNum = 2) {
		//include code here load level 2 from txt file
		return _pLevel;
	}
	if (_LevelNum = 3) {
		//include code here load level 3 from txt file
		return _pLevel;
	}
	else {
		//include code here load level 4 from txt file
		return _pLevel;
	}
}


std::vector<CPlayer> CGameEngine::GetPlayerList()
{
	return playerList;
}