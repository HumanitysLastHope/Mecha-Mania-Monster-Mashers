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

	std::vector<CPlayer>& GetPlayerList();


private:
	CPlayer player1;
	CPlayer player2;
	CPlayer player3;
	CPlayer player4;
	CBoard _pLevel;
	std::vector<CPlayer> playerList = { player1, player2, player3, player4 };
	IGameState* m_pCurGameState;
};

