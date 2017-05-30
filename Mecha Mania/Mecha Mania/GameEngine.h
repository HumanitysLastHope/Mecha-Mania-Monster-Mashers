#include <vector>
#include <conio.h>
#include <iostream>

#include "Bullet.h"
#include "Player.h"
#include "Board.h"
#include "Tile.h"


#pragma once

class IGameState;
class ExecutingCMDState;
class CGettingPlayerMovesState;
class CMovingBulletsState;

class CGameEngine
{
public:
	CGameEngine(int _playerCount);
	~CGameEngine();

	int playerAliveCount;// = 4;

	void Step();
	bool PitCheck();
	void Draw();
	void ChangeState(IGameState* _state);
	CBoard& LoadBoard(int _LevelNum, int _playerCount);
	CBoard& GetBoard();
	void WaterCheck(CPlayer* _pPlayer);
	void SetNewFirstPlayer();
	void DrawFirstPlayer(CPlayer _Player, int _iX, int _iY);

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

	bool inGetState;

	ExecutingCMDState* GetExecutingState();
	CGettingPlayerMovesState* GetGettingInputState();
	CMovingBulletsState* GetMovBulletState();
	
	void SetMoveList(int _iNum, char _cOut);
	void ResetMoveList();

	void ActionText(char _cAction, CMecha* _pMecha, bool _bDied);

	std::vector<std::string>& GetBattleActionText();
	void ResetBattleActionText();

	void PrintBattleActionText();

private:
	CBoard m_Level;
	CPlayer m_Player1;
	CPlayer m_Player2;
	CPlayer m_Player3;
	CPlayer m_Player4;
	CPlayer* m_pWinner;

	int m_iCursorPos = 9;

	std::vector<CPlayer> m_PlayerList;
	std::vector<CBullet*> m_vecpBulletList;
	//std::vector<CMine*> m_vecMineList;

	
	ExecutingCMDState* m_pstateExecuting;
	CGettingPlayerMovesState* m_pstateGetInput;
	CMovingBulletsState* m_pstateMovBullet;

	//int m_iMoveDraw;
	char m_rgMoveList[6] = { ' ', ' ', ' ', ' ', ' ', ' ' };
	
	IGameState* m_pCurGameState;

	std::vector<std::string> m_vecBattleActionText;
};

