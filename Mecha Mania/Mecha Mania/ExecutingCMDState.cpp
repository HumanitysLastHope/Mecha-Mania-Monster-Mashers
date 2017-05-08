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

void ExecutingCMDState::ExecuteUserInput(CGameEngine* _pGameEngine)
{
	system("CLS"); //clear screen
	_pGameEngine->Draw(); //redraw
	_getch(); //show user screen
	system("CLS"); //clear again before creating new screens
	std::vector<CPlayer>& playerList = _pGameEngine->GetPlayerList();
	int playerCommand;
	int iOppositeDirection;
	EDIRECTION iOpposite;

	//for (int j = 0; j < 3; j++)
	//{

	for (int i = 0; i < _pGameEngine->playerAliveCount; i++)
	{
		playerCommand = playerList[i].GetMoveList().front();
		playerList[i].GetMoveList().pop();

		switch (playerCommand)
		{
		case 11:
		{
			playerList[i].GetMecha()->Move(playerList[i].GetMecha()->GetDirection());
			_pGameEngine->Draw();
			_getch();
			system("CLS");


			//std::cout << i << ": " << playerList[i].GetMecha()->GetDirection();
			break;
		}
		case 12:
		{
			playerList[i].GetMecha()->Move(playerList[i].GetMecha()->GetDirection());
			_pGameEngine->Draw();
			_getch();

			system("CLS");


			playerList[i].GetMecha()->Move(playerList[i].GetMecha()->GetDirection());
			_pGameEngine->Draw();
			_getch();

			system("CLS");


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
			_pGameEngine->Draw();
			_getch();

			system("CLS");

			break;
		}
		case 14:
		{
			iOppositeDirection = (playerList[i].GetMecha()->GetDirection() + 2) % 4;
			playerList[i].GetMecha()->Move(static_cast<EDIRECTION>(iOppositeDirection));
			_pGameEngine->Draw();
			_getch();
			system("CLS");


			//std::cout << i << ": " << playerList[i].GetMecha()->GetDirection();
			break;
		}
		}
	}
//	}
	

	_pGameEngine->ChangeState(new CGettingPlayerMovesState);
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