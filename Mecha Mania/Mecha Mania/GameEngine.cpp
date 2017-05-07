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


std::vector<CPlayer> CGameEngine::GetPlayerList()
{
	return playerList;
}