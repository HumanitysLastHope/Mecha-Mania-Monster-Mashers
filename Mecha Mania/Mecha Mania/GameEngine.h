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

	std::vector<CPlayer> GetPlayerList();

private:
	CPlayer player1;
	std::vector<CPlayer> playerList = { player1 };
};

