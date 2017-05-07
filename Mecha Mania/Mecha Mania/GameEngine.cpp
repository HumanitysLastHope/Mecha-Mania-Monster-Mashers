#include "GameEngine.h"



CGameEngine::CGameEngine()
{
}


CGameEngine::~CGameEngine()
{
}

void CGameEngine::Step()
{
}

void CGameEngine::Draw()
{
}

void CGameEngine::ChangeState(IGameState * _state)
{
}

CBoard& CGameEngine::LoadBoard(int _LevelNum) {
	CBoard* _pLevel = new CBoard;
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++i)
		{
			CTile* _pTile = new CTile;
			_pLevel->SetTile(j, i, _pTile);
		}
	}
	if (_LevelNum = 1) {
		//include code here to make the level 1 unique
		return *_pLevel;
	}
	if (_LevelNum = 2) {
		//include code here to make the level 2 unique
		return *_pLevel;
	}
	if (_LevelNum = 3) {
		//include code here to make the level 3 unique
		return *_pLevel;
	}
	else {
		//include code here to make the level 4 unique
		return *_pLevel;
	}
}
