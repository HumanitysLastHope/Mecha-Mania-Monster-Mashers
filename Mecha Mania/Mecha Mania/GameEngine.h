#include <vector>
#include "Player.h"

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

	CPlayer player1;
	CPlayer player2;
	CPlayer player3;
	CPlayer player4;

	std::vector<CPlayer> playerList = { player1,player2, player3, player4 };
};

