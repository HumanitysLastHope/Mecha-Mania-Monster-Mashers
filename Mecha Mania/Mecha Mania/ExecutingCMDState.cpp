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

	int i = 0; // Doesn't matter that it's reset

	if (z < playerList.size()-1)
	{
		z++; // NEXT PLAYER

	}
	else
	{
		z = 0;
	}

	i = _pGameEngine->m_CommandOrder[z]; // Determine player using command order


	if (playerList[i].GetMoveList().empty() == true && playerList[i].bDead == false) // If alive and no commands left to execute
	{
		_pGameEngine->SetNewFirstPlayer();
		_pGameEngine->inGetState = true;

  		_pGameEngine->ChangeState(_pGameEngine->GetGettingInputState());
		_pGameEngine->GetGettingInputState()->ResetZ();
		_pGameEngine->ResetBattleActionText();
		_getch();
		system("CLS");
   		return;
	}

	GotoXY(4, 22);
	std::cout << "Player " << i + 1;

	_pGameEngine->WaterCheck(&(playerList[i]));
	playerList[i].bDead = playerList[i].CheckDeath();
	//std::cout << i << " dead = " << playerList[i].bDead;
	_getch();

	int playerCommand;
	int iOppositeDirection;

	if (playerList[i].bDead == false) // Get alive players command
	{
		playerCommand = playerList[i].GetMoveList().front();
		playerList[i].GetMoveList().pop();
	}
	else // Skip dead player's turn
	{
		return;
	}

	switch (playerCommand)
	{
	case 11: // Move 1
	{
		playerList[i].GetMecha()->Move(playerList[i].GetMecha()->GetDirection(), _pGameEngine);

		break;
	}
	case 12: // Move 2
	{
		playerList[i].GetMecha()->Move(playerList[i].GetMecha()->GetDirection(), _pGameEngine);
		system("CLS");
		_pGameEngine->Draw();

		playerList[i].bDead = playerList[i].CheckDeath();

		if (playerList[i].bDead == true)
		{
			return;
		}
		playerList[i].GetMecha()->Move(playerList[i].GetMecha()->GetDirection(), _pGameEngine);

		break;
	}
	case 13: // Move 3
	{
		playerList[i].GetMecha()->Move(playerList[i].GetMecha()->GetDirection(), _pGameEngine);
		system("CLS");
		_pGameEngine->Draw();

		playerList[i].bDead = playerList[i].CheckDeath();

		if (playerList[i].bDead == true)
		{
			return;
		}

		playerList[i].GetMecha()->Move(playerList[i].GetMecha()->GetDirection(),_pGameEngine);

		system("CLS");
		_pGameEngine->Draw();

		playerList[i].bDead = playerList[i].CheckDeath();
		if (playerList[i].bDead == true)
		{
			return;
		}

		playerList[i].GetMecha()->Move(playerList[i].GetMecha()->GetDirection(), _pGameEngine);

		break;
	}
	case 14: // Move backwards
	{
		iOppositeDirection = (playerList[i].GetMecha()->GetDirection() + 2) % 4;
		playerList[i].GetMecha()->Move(static_cast<EDIRECTION>(iOppositeDirection), _pGameEngine);

		break;
	}
	case 21: // Clockwise
	{

		playerList[i].GetMecha()->Rotate(CLOCKWISE);
		break;
	}
	case 22: // Anti-Clockwise
	{
		playerList[i].GetMecha()->Rotate(ANTICLOCKWISE);
		break;
	}
	case 23: // Flip
	{
		playerList[i].GetMecha()->Rotate(ONEEIGHTY);
		break;
	}
	case 31: // Shoot
	{
		playerList[i].GetMecha()->Shoot(*_pGameEngine);
		system("CLS");
		_pGameEngine->Draw();
		break;
	}
	case 32: // Push
	{
		CMovable* objToPush;
		objToPush = playerList[i].GetMecha()->WhatToPush(_pGameEngine);
	

		if (objToPush != nullptr)
		{
			if (objToPush->Move(playerList[i].GetMecha()->GetMechaFacingDirect(), _pGameEngine) != false)
			{
				objToPush->Move(playerList[i].GetMecha()->GetMechaFacingDirect(), _pGameEngine);

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
		playerList[i].GetMecha()->PlaceMine();
		break;
	}
	}
	
	//std::cout << i << "'s health is: " << playerList[i].GetMecha()->GetHealth();
	//_getch();

	//Move bullets.....
	_pGameEngine->ChangeState(_pGameEngine->GetMovBulletState());

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

void ExecutingCMDState::ResetZ()
{
	z = -1;
}
