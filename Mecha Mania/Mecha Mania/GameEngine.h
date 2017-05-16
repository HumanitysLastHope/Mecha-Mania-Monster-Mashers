#include <vector>
#include <conio.h>
#include <iostream>

#include "Bullet.h"
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
	bool PitCheck();
	void Draw();
	void ChangeState(IGameState* _state);
	CBoard& LoadBoard(int _LevelNum);
	CBoard& GetBoard();
	void WaterCheck(CPlayer* _pPlayer);
	void SetNewFirstPlayer();

	CBullet* SpawnBullet(const TPosition&, EDIRECTION);
	void DestroyBullet(CBullet*);

	std::vector<int> m_CommandOrder;

	std::vector<CPlayer>& GetPlayerList();
	std::vector<CBullet*>& GetBulletList();

	static void Run();
	bool BulletCollisionTest();

	// Actually destroy bullets in a safe location when we are not iterating through the list of bullets
	void ActuallyDestroyBullets();
	bool m_bBulletsToDestroy;


private:
	CBoard m_Level;
	CPlayer m_Player1;
	CPlayer m_Player2;
	CPlayer m_Player3;
	CPlayer m_Player4;
	CPlayer* m_pWinner;
	std::vector<CPlayer> m_PlayerList = { m_Player1, m_Player2, m_Player3, m_Player4};
	std::vector<CBullet*> m_vecpBulletList;
	//std::vector<CMine*> m_vecMineList;


	
	IGameState* m_pCurGameState;
};

