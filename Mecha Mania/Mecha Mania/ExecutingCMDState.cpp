#include "ExecutingCMDState.h"
#include <queue>
#include <iostream>
#include <conio.h>

#include "GettingPlayerMovesState.h"
#include "MovingBulletsState.h"

ExecutingCMDState::ExecutingCMDState()
{
	z = -1; // INITIAL DO NOT CHANGE
	j = 0;
}


ExecutingCMDState::~ExecutingCMDState()
{
}

void ExecutingCMDState::ExecuteUserInput(CGameEngine* _pGameEngine)
{
	std::vector<CPlayer>& playerList = _pGameEngine->GetPlayerList();

	int i = 0; // Doesn't matter that it's reset

	if (z < 3)
	{
		z++; // NEXT PLAYER
	}
	else
	{
		z = 0;
	}

	i = _pGameEngine->m_CommandOrder[z];

	std::cout << i << "'s health is: " << playerList[i].GetMecha()->GetHealth();
	_getch();


	if (playerList[i].GetMoveList().empty() == true && playerList[i].bDead == false)
	{
		_pGameEngine->SetNewFirstPlayer();
		_pGameEngine->ChangeState(new CGettingPlayerMovesState);
   		return;
	}

	_pGameEngine->WaterCheck(&(playerList[i]));
	
	//system("CLS"); //clear again before creating new screens
//	std::vector<CPlayer>& playerList = _pGameEngine->GetPlayerList();
	playerList[i].bDead = playerList[i].CheckDeath();

	int playerCommand;
	int iOppositeDirection;

	if (playerList[i].bDead == false)
	{
		playerCommand = playerList[i].GetMoveList().front();
		playerList[i].GetMoveList().pop();
	}
	else
	{
		return;
	}

	switch (playerCommand)
	{
	case 11:
	{
		playerList[i].GetMecha()->Move(playerList[i].GetMecha()->GetDirection());
		//_pGameEngine->WaterCheck(&(playerList[i]));

		break;
	}
	case 12:
	{
		playerList[i].GetMecha()->Move(playerList[i].GetMecha()->GetDirection());
		//_pGameEngine->WaterCheck(&(playerList[i]));
		_pGameEngine->Draw();
		_getch();
		system("CLS");

		playerList[i].bDead = playerList[i].CheckDeath();
		if (playerList[i].bDead == true)
		{
			return;
		}

		playerList[i].GetMecha()->Move(playerList[i].GetMecha()->GetDirection());
		//_pGameEngine->WaterCheck(&(playerList[i]));
		break;
	}
	case 13:
	{
		playerList[i].GetMecha()->Move(playerList[i].GetMecha()->GetDirection());
		//_pGameEngine->WaterCheck(&(playerList[i]));
		_pGameEngine->Draw();
		_getch();
		system("CLS");

		playerList[i].bDead = playerList[i].CheckDeath();
		if (playerList[i].bDead == true)
		{
			return;
		}

		playerList[i].GetMecha()->Move(playerList[i].GetMecha()->GetDirection());
		//_pGameEngine->WaterCheck(&(playerList[i]));
		_pGameEngine->Draw();
		_getch();
		system("CLS");

		playerList[i].bDead = playerList[i].CheckDeath();
		if (playerList[i].bDead == true)
		{
			return;
		}

		playerList[i].GetMecha()->Move(playerList[i].GetMecha()->GetDirection());
		//_pGameEngine->WaterCheck(&(playerList[i]));
		break;
	}
	case 14:
	{
		iOppositeDirection = (playerList[i].GetMecha()->GetDirection() + 2) % 4;
		playerList[i].GetMecha()->Move(static_cast<EDIRECTION>(iOppositeDirection));
		//_pGameEngine->WaterCheck(&(playerList[i]));
		break;
	}
	case 21: //clockwise
	{

		playerList[i].GetMecha()->Rotate(CLOCKWISE);
		break;
	}
	case 22:
	{
		playerList[i].GetMecha()->Rotate(ANTICLOCKWISE);
		break;
	}
	case 23:
	{
		playerList[i].GetMecha()->Rotate(ONEEIGHTY);
		break;
	}
	case 31:
	{
		playerList[i].GetMecha()->Shoot(*_pGameEngine);
		break;
	}
	case 32:
	{
		CMovable* objToPush;
		objToPush = playerList[i].GetMecha()->WhatToPush();

		if (objToPush != nullptr)
		{
			if (objToPush->Move(playerList[i].GetMecha()->GetMechaFacingDirect()) != false)
			{
				objToPush->Move(playerList[i].GetMecha()->GetMechaFacingDirect());
			}
		}
		
		break;
	}
	case 33:
	{
		playerList[i].GetMecha()->PlaceMine();
		break;
	}
	}
	
	//_pGameEngine->Draw();
	//_getch();
	//_pGameEngine->WaterCheck(&(playerList[i]));
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
		
		//Move bullets.....
		auto pTemp = new CMovingBulletsState;	
		pTemp->Step(_pGameEngine);
		delete pTemp;
		_pGameEngine->BulletCollisionTest();

		if (_pGameEngine->m_bBulletsToDestroy)
		{
			_pGameEngine->ActuallyDestroyBullets();
		}
}