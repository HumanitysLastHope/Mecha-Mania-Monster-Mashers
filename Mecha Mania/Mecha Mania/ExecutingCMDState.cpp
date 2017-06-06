#include "ExecutingCMDState.h"
#include <queue>
#include <iostream>
#include <conio.h>

#include "GettingPlayerMovesState.h"
#include "MovingBulletsState.h"
#include "Util.h"

ExecutingCMDState::ExecutingCMDState()
{
	//z = -1; // INITIAL DO NOT CHANGE
	//j = 0;
}


ExecutingCMDState::~ExecutingCMDState()
{
}


void ExecutingCMDState::ExecuteUserInput(CGameEngine* _pGameEngine)
{

	std::vector<CPlayer>& playerList = _pGameEngine->GetPlayerList();

	int iRealPlayerCount = 0; // Doesn't matter that it's reset

	if (iLocCount < playerList.size()-1)
	{
		iLocCount++; // NEXT PLAYER
	}
	else
	{
		iLocCount = 0;
	}

	iRealPlayerCount = _pGameEngine->m_CommandOrder[iLocCount]; // Determine player using command order


	if (playerList[iRealPlayerCount].GetMoveList().empty() == true && playerList[iRealPlayerCount].bDead == false) // If alive and no commands left to execute
	{
  		_pGameEngine->SetNewFirstPlayer();
		_pGameEngine->inGetState = true;

		_pGameEngine->GetGettingInputState()->ResetZ();
		_pGameEngine->ResetBattleActionText();
		_pGameEngine->ResetMoveList();
  		_pGameEngine->ChangeState(_pGameEngine->GetGettingInputState());


		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		//getline(cin, response);
		
		//_getch();
		system("CLS");
   		return;
	}

	

	_pGameEngine->WaterCheck(&(playerList[iRealPlayerCount]));
	playerList[iRealPlayerCount].bDead = playerList[iRealPlayerCount].CheckDeath();
	//std::cout << i << " dead = " << playerList[i].bDead;
	//_getch();

	int playerCommand;
	int iOppositeDirection;

	if (playerList[iRealPlayerCount].bDead == false) // Get alive players command
	{
		playerCommand = playerList[iRealPlayerCount].GetMoveList().front();
		playerList[iRealPlayerCount].GetMoveList().pop();
	}
	else // Skip dead player's turn
	{
		return;
	}

	if (playerList[iRealPlayerCount].GetMoveList().size() == 2)
	{
		_pGameEngine->SetMoveList(0, playerList[iRealPlayerCount].GetOutMove().at(0));
		_pGameEngine->SetMoveList(1, playerList[iRealPlayerCount].GetOutMove().at(1));

	}
	else if (playerList[iRealPlayerCount].GetMoveList().size() == 1)
	{
		_pGameEngine->SetMoveList(0, playerList[iRealPlayerCount].GetOutMove().at(0));
		_pGameEngine->SetMoveList(1, playerList[iRealPlayerCount].GetOutMove().at(1));
		_pGameEngine->SetMoveList(2, playerList[iRealPlayerCount].GetOutMove().at(2));
		_pGameEngine->SetMoveList(3, playerList[iRealPlayerCount].GetOutMove().at(3));

	}
	else if (playerList[iRealPlayerCount].GetMoveList().size() == 0)
	{
		_pGameEngine->SetMoveList(0, playerList[iRealPlayerCount].GetOutMove().at(0));
		_pGameEngine->SetMoveList(1, playerList[iRealPlayerCount].GetOutMove().at(1));
		_pGameEngine->SetMoveList(2, playerList[iRealPlayerCount].GetOutMove().at(2));
		_pGameEngine->SetMoveList(3, playerList[iRealPlayerCount].GetOutMove().at(3));
		_pGameEngine->SetMoveList(4, playerList[iRealPlayerCount].GetOutMove().at(4));
		_pGameEngine->SetMoveList(5, playerList[iRealPlayerCount].GetOutMove().at(5));

	}

	GotoXY(4, 22);
	std::cout << "Player " << iRealPlayerCount + 1;

	switch (playerCommand)
	{
	case 11: // Move 1
	{
		playerList[iRealPlayerCount].GetMecha()->Move(playerList[iRealPlayerCount].GetMecha()->GetDirection(), _pGameEngine);

		break;
	}
	case 12: // Move 2
	{
		playerList[iRealPlayerCount].GetMecha()->Move(playerList[iRealPlayerCount].GetMecha()->GetDirection(), _pGameEngine);
		system("CLS");
		_pGameEngine->Draw();

		GotoXY(4, 22);
		std::cout << "Player " << iRealPlayerCount + 1;
		_pGameEngine->PrintBattleActionText();

		playerList[iRealPlayerCount].bDead = playerList[iRealPlayerCount].CheckDeath();

		if (playerList[iRealPlayerCount].bDead == true)
		{
			return;
		}
		Sleep(1000);
		playerList[iRealPlayerCount].GetMecha()->Move(playerList[iRealPlayerCount].GetMecha()->GetDirection(), _pGameEngine);

		break;
	}
	case 13: // Move 3
	{
		playerList[iRealPlayerCount].GetMecha()->Move(playerList[iRealPlayerCount].GetMecha()->GetDirection(), _pGameEngine);
		system("CLS");
		_pGameEngine->Draw();

		GotoXY(4, 22);
		std::cout << "Player " << iRealPlayerCount + 1;
		_pGameEngine->PrintBattleActionText();

		playerList[iRealPlayerCount].bDead = playerList[iRealPlayerCount].CheckDeath();

		if (playerList[iRealPlayerCount].bDead == true)
		{
			return;
		}
		Sleep(1000);
		playerList[iRealPlayerCount].GetMecha()->Move(playerList[iRealPlayerCount].GetMecha()->GetDirection(),_pGameEngine);

		system("CLS");
		_pGameEngine->Draw();

		GotoXY(4, 22);
		std::cout << "Player " << iRealPlayerCount + 1;
		_pGameEngine->PrintBattleActionText();

		playerList[iRealPlayerCount].bDead = playerList[iRealPlayerCount].CheckDeath();
		if (playerList[iRealPlayerCount].bDead == true)
		{
			return;
		}
		Sleep(1000);
		playerList[iRealPlayerCount].GetMecha()->Move(playerList[iRealPlayerCount].GetMecha()->GetDirection(), _pGameEngine);

		break;
	}
	case 14: // Move backwards
	{
		iOppositeDirection = (playerList[iRealPlayerCount].GetMecha()->GetDirection() + 2) % 4;
		playerList[iRealPlayerCount].GetMecha()->Move(static_cast<EDIRECTION>(iOppositeDirection), _pGameEngine);

		break;
	}
	case 21: // Clockwise
	{

		playerList[iRealPlayerCount].GetMecha()->Rotate(CLOCKWISE);
		break;
	}
	case 22: // Anti-Clockwise
	{
		playerList[iRealPlayerCount].GetMecha()->Rotate(ANTICLOCKWISE);
		break;
	}
	case 23: // Flip
	{
		playerList[iRealPlayerCount].GetMecha()->Rotate(ONEEIGHTY);
		break;
	}
	case 31: // Shoot
	{
		playerList[iRealPlayerCount].GetMecha()->Shoot(*_pGameEngine);
		system("CLS");
		_pGameEngine->Draw();
		break;
	}
	case 32: // Push
	{
		CMovable* objToPush;
		objToPush = playerList[iRealPlayerCount].GetMecha()->WhatToPush(_pGameEngine);

		if (objToPush != nullptr)
		{
			if (objToPush->Move(playerList[iRealPlayerCount].GetMecha()->GetMechaFacingDirect(), _pGameEngine) != false)
			{
				CBullet* pBullet =  dynamic_cast<CBullet*>(objToPush);
				if (pBullet)
				{
					pBullet->SetDirection(playerList[iRealPlayerCount].GetMecha()->GetDirection());
				}
				objToPush->Move(playerList[iRealPlayerCount].GetMecha()->GetMechaFacingDirect(), _pGameEngine);


			}
			else
			{
				_pGameEngine->GetBattleActionText().pop_back();
			}
		}
		
		break;
	}
	case 33: // Place mine
	{
		playerList[iRealPlayerCount].GetMecha()->PlaceMine();
		break;
	}
	}

	GotoXY(4, 22);
	std::cout << "Player " << iRealPlayerCount + 1;
	_pGameEngine->PrintBattleActionText();
	
	Sleep(1000);
	//std::cout << i << "'s health is: " << playerList[i].GetMecha()->GetHealth();
	//_getch();

	//Move bullets.....
	_pGameEngine->ChangeState(_pGameEngine->GetMovBulletState());
	_pGameEngine->inGetState = false;
}


void ExecutingCMDState::Init()
{
	
}

void ExecutingCMDState::Cleanup()
{

}
void ExecutingCMDState::Draw(CGameEngine * _pGameEngine)
{

}

void ExecutingCMDState::Step(CGameEngine * _pGameEngine)
{
	ExecuteUserInput(_pGameEngine);

	
}

void ExecutingCMDState::ResetLocalCount()
{
	iLocCount = -1;
}
