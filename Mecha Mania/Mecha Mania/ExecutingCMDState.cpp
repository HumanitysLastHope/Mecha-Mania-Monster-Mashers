#include "ExecutingCMDState.h"
#include <queue>
#include <iostream>
#include "GettingPlayerMovesState.h"
#include <conio.h>



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
	int playerCommand;
	int iOppositeDirection;
	
	playerCommand = playerList[i].GetMoveList().front();
	playerList[i].GetMoveList().pop();

	switch (playerCommand)
	{
	case 11:
	{
		playerList[i].GetMecha()->Move(playerList[i].GetMecha()->GetDirection());
		break;
	}
	case 12:
	{
		playerList[i].GetMecha()->Move(playerList[i].GetMecha()->GetDirection());
		_pGameEngine->Draw();
		_getch();
		system("CLS");

		playerList[i].GetMecha()->Move(playerList[i].GetMecha()->GetDirection());

		break;
	}
	case 13:
	{
		playerList[i].GetMecha()->Move(playerList[i].GetMecha()->GetDirection());
		_pGameEngine->Draw();
		_getch();
		system("CLS");

		playerList[i].GetMecha()->Move(playerList[i].GetMecha()->GetDirection());
		_pGameEngine->Draw();
		_getch();
		system("CLS");

		playerList[i].GetMecha()->Move(playerList[i].GetMecha()->GetDirection());
		break;
	}
	case 14:
	{
		iOppositeDirection = (playerList[i].GetMecha()->GetDirection() + 2) % 4;
		playerList[i].GetMecha()->Move(static_cast<EDIRECTION>(iOppositeDirection));
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
		playerList[i].GetMecha()->Shoot();
		break;
	}
	case 32:
	{
		playerList[i].GetMecha()->Push();
		break;
	}
	case 33:
	{
		playerList[i].GetMecha()->PlaceMine();
		break;
	}
	}
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
	system("CLS");
	_pGameEngine->Draw();
	_getch();
	system("CLS");

	for (int j = 0; j < 3; j++) // EXECUTE 3 ORDERS
	{
		for (int i = 0; i < _pGameEngine->playerAliveCount; i++) //EXECUTE EACH PLAYERS ORDER
		{
			ExecuteUserInput(_pGameEngine, i);
			//bullet move phase goes here
			_pGameEngine->CollisionCheck();
			_pGameEngine->Draw();
			_getch();
			system("CLS");
		}

		
	}
	
	_pGameEngine->ChangeState(new CGettingPlayerMovesState);

}