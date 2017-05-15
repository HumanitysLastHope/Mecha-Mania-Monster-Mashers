#include "ExecutingCMDState.h"
#include <queue>
#include <iostream>
#include <conio.h>

#include "GettingPlayerMovesState.h"
#include "MovingBulletsState.h"

ExecutingCMDState::ExecutingCMDState()
{
}


ExecutingCMDState::~ExecutingCMDState()
{
}

void ExecutingCMDState::ExecuteUserInput(CGameEngine* _pGameEngine, int i)
{

	//system("CLS"); //clear screen
	//_pGameEngine->Draw(); //redraw
	//_getch(); //show user screen
	system("CLS"); //clear again before creating new screens
	std::vector<CPlayer>& playerList = _pGameEngine->GetPlayerList();
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
	bool waterCheck = false;
	int i = 0;
	system("CLS");
	_pGameEngine->Draw();
	_getch();
	system("CLS");
	std::vector<CPlayer>& playerList = _pGameEngine->GetPlayerList();

	for (int j = 0; j < 3; j++) // EXECUTE 3 ORDERS
	{

		for (int z = 0; z < 4; z++) //EXECUTE EACH PLAYERS ORDER
		{
			i = _pGameEngine->m_CommandOrder[z];
			_pGameEngine->WaterCheck(&(playerList[i]));
			ExecuteUserInput(_pGameEngine, i);
			_pGameEngine->PitCheck();

			//Move bullets.....
			auto pTemp = new CMovingBulletsState;	
			//_getch();
			system("CLS");
			_pGameEngine->Draw();

			pTemp->Step(_pGameEngine);
			_getch();
			system("CLS");

			//system("CLS");


			delete pTemp;



			_pGameEngine->BulletCollisionTest();



			if (_pGameEngine->m_bBulletsToDestroy)
			{
				_pGameEngine->ActuallyDestroyBullets();
			}


			for (int l = 0; l < _pGameEngine->playerAliveCount; l++)
			{
				playerList[l].bDead = playerList[l].CheckDeath();
			}
		

			_pGameEngine->Draw();
			std::cout << "Player: " << i << " HP: ";
			std::cout << playerList[i].GetMecha()->GetHealth();
			_getch();
			system("CLS");
		}

		
	}
		
		//_pGameEngine->CollisionCheck(true);

	_pGameEngine->SetNewFirstPlayer();

	_pGameEngine->ChangeState(new CGettingPlayerMovesState);

}