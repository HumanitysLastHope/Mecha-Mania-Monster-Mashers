#include <vector>
#include "Player.h"
#include "Board.h"
#include "Tile.h"
#include <iostream>

#pragma once

class IGameState;

class CGameEngine
{
public:
	CGameEngine();
	~CGameEngine();

	int playerAliveCount = 4;

	void Step();
	void Draw();
	void ChangeState(IGameState* _state);
	CBoard& LoadBoard(int _LevelNum);

	std::vector<CPlayer> GetPlayerList();

private:
	CBoard m_Level;
	CPlayer m_Player1;
	CPlayer m_Player2;
	CPlayer m_Player3;
	CPlayer m_Player4;
	std::vector<CPlayer> m_PlayerList = { m_Player1 };
	IGameState* m_pCurGameState;
};

