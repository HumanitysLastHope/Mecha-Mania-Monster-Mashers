#include <vector>
#include <conio.h>
#include <iostream>
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
	bool CollisionCheck(bool bWaterCheck);
	void Draw();
	void ChangeState(IGameState* _state);
	CBoard& LoadBoard(int _LevelNum);
	void WaterCheck(CPlayer* _pPlayer);


	std::vector<CPlayer>& GetPlayerList();


	static void Run();
private:
	CBoard m_Level;
	CPlayer m_Player1;
	CPlayer m_Player2;
	CPlayer m_Player3;
	CPlayer m_Player4;
	std::vector<CPlayer> m_PlayerList = { m_Player1, m_Player2, m_Player3, m_Player4};
	IGameState* m_pCurGameState;
};

