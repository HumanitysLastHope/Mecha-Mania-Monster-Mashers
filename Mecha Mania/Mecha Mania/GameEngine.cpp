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
		//include code here to make the level 1 unique
		return _pLevel;
	}
	if (_LevelNum = 2) {
		//include code here to make the level 2 unique
		return _pLevel;
	}
	if (_LevelNum = 3) {
		//include code here to make the level 3 unique
		return _pLevel;
	}
	else {
		//include code here to make the level 4 unique
		return _pLevel;
	}
}


std::vector<CPlayer> CGameEngine::GetPlayerList()
{
	return playerList;
}