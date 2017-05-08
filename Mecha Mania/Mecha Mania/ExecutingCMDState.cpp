#include "ExecutingCMDState.h"
#include <queue>
#include <iostream>
#include "GettingPlayerMovesState.h"




ExecutingCMDState::ExecutingCMDState()
{
}


ExecutingCMDState::~ExecutingCMDState()
{
}

void ExecutingCMDState::ExecuteUserInput(CGameEngine* _pGameEngine)
{
	std::vector<CPlayer>& playerList = _pGameEngine->GetPlayerList();
	int playerCommand;

	//playerList[0].GetMecha()->SetGridPosition({ 1,1 });


	for (int i = 0; i < _pGameEngine->playerAliveCount; i++)
	{
		playerCommand = playerList[i].GetMoveList().front();
		playerList[i].GetMoveList().pop();
		switch (playerCommand)
		{
		case 11:
		{
			playerList[i].GetMecha()->Move(playerList[i].GetMecha()->GetDirection());
			break;
		}
		}
	}

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