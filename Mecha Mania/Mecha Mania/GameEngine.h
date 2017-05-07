#include <vector>
#include "Player.h"
#include "Board.h"
#include "Tile.h"

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

	CPlayer player1;
	CPlayer player2;
	CPlayer player3;
	CPlayer player4;

	std::vector<CPlayer> playerList = { player1,player2, player3, player4 };
private:
	IGameState* m_pCurGameState;

};

