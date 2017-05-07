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
}

void CGameEngine::Draw()
{
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
