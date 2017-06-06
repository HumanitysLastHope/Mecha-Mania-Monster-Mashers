#include "GettingPlayerMovesState.h"
#include "GameEngine.h"
#include <conio.h>
#include <iostream>
#include "ExecutingCMDState.h"

//
//GettingPlayerMovesStates::GettingPlayerMovesStates()
//{
//}
//
//
//GettingPlayerMovesStates::~GettingPlayerMovesStates()
//{
//}

CGettingPlayerMovesState::CGettingPlayerMovesState()
{
	iRealPlayerCount = 0;
	iMoveCount = 0;
}

CGettingPlayerMovesState::~CGettingPlayerMovesState()
{
}

void CGettingPlayerMovesState::ProcessUserInput(CGameEngine* _pGameEngine)
{
	std::vector<CPlayer>& playerList = _pGameEngine->GetPlayerList();

	iRealPlayerCount = _pGameEngine->m_CommandOrder[iLocalCount];

	if (playerList[iRealPlayerCount].bDead == true)
	{
		if (iRealPlayerCount < playerList.size()-1 && iLocalCount< playerList.size() - 1)
		{
			iRealPlayerCount++;
			iLocalCount++;
		}
		else
		{
			iRealPlayerCount = 0;
			iLocalCount = 0;
			system("CLS");
			_pGameEngine->inGetState = false;
			_pGameEngine->ChangeState(_pGameEngine->GetExecutingState());
		}
	}
	else
	{
		CPlayer playerGetMove = playerList[0];
		int iPlayerInput;
		bool bValidMove = false;

		while (bValidMove == false)
		{
			iPlayerInput = _getch() - '0';
			


			switch (iPlayerInput)
			{
			case 1: // Move sub menu
			{
				iPlayerInput = 0;

				_pGameEngine->SetMoveList(iMoveCount * 2, '*');
				_pGameEngine->Draw();

				playerList[iRealPlayerCount].GetOutMove().push_back('1');

				while (bValidMove == false)
				{
					iPlayerInput = _getch() - '0';
					bValidMove = true;


					if (iPlayerInput == 1)
					{
						_pGameEngine->SetMoveList(iMoveCount * 2 + 1, '*');
						playerList[iRealPlayerCount].GetMoveList().push(MOVEONE);
						playerList[iRealPlayerCount].GetOutMove().push_back('1');

					}
					else if (iPlayerInput == 2)
					{
						_pGameEngine->SetMoveList(iMoveCount * 2 + 1, '*');
						playerList[iRealPlayerCount].GetMoveList().push(MOVETWO);
						playerList[iRealPlayerCount].GetOutMove().push_back('2');


					}
					else if (iPlayerInput == 3)
					{
						_pGameEngine->SetMoveList(iMoveCount * 2 + 1, '*');
						playerList[iRealPlayerCount].GetMoveList().push(MOVETHREE);
						playerList[iRealPlayerCount].GetOutMove().push_back('3');


					}
					else if (iPlayerInput == 4)
					{
						_pGameEngine->SetMoveList(iMoveCount * 2 + 1, '*');
						playerList[iRealPlayerCount].GetMoveList().push(MOVEBACK);
						playerList[iRealPlayerCount].GetOutMove().push_back('4');


					}
					else
					{
						//incorrect input
						bValidMove = false;
					}
				}
				break;
			}
			case 2: // Rotate sub menu
			{
				iPlayerInput = 0;
				_pGameEngine->SetMoveList(iMoveCount * 2, '*');
				_pGameEngine->Draw();
				playerList[iRealPlayerCount].GetOutMove().push_back('2');


				while (bValidMove == false)
				{
					iPlayerInput = _getch() - '0';
					bValidMove = true;

					if (iPlayerInput == 1)
					{
						_pGameEngine->SetMoveList(iMoveCount * 2 + 1, '*');
						playerList[iRealPlayerCount].GetMoveList().push(ROTATECLOCKWISE);
						playerList[iRealPlayerCount].GetOutMove().push_back('1');

					}
					else if (iPlayerInput == 2)
					{
						_pGameEngine->SetMoveList(iMoveCount * 2 + 1, '*');
						playerList[iRealPlayerCount].GetMoveList().push(ROTATEANTICLOCKWISE);
						playerList[iRealPlayerCount].GetOutMove().push_back('2');


					}
					else if (iPlayerInput == 3)
					{
						_pGameEngine->SetMoveList(iMoveCount * 2 + 1, '*');
						playerList[iRealPlayerCount].GetMoveList().push(FLIP);
						playerList[iRealPlayerCount].GetOutMove().push_back('3');


					}
					else
					{
						//incorrect input
						bValidMove = false;
					}
				}
				break;
			}
			case 3: // Attack sub menu
			{
				iPlayerInput = 0;
				_pGameEngine->SetMoveList(iMoveCount * 2, '*');
				_pGameEngine->Draw();

				playerList[iRealPlayerCount].GetOutMove().push_back('3');


				while (bValidMove == false)
				{
					iPlayerInput = _getch() - '0';
					bValidMove = true;

					

					if (iPlayerInput == 1)
					{
						_pGameEngine->SetMoveList(iMoveCount * 2 + 1, '*');
						playerList[iRealPlayerCount].GetMoveList().push(SHOOT);
						playerList[iRealPlayerCount].GetOutMove().push_back('1');

					}
					else if (iPlayerInput == 2)
					{
						_pGameEngine->SetMoveList(iMoveCount * 2 + 1, '*');
						playerList[iRealPlayerCount].GetMoveList().push(PUSH);
						playerList[iRealPlayerCount].GetOutMove().push_back('2');


					}
					else if (iPlayerInput == 3)
					{
						_pGameEngine->SetMoveList(iMoveCount * 2 + 1, '*');
						playerList[iRealPlayerCount].GetMoveList().push(PLACEMINE);
						playerList[iRealPlayerCount].GetOutMove().push_back('3');


					}
					else
					{
						//incorrect input
						bValidMove = false;
					}

				}
				break;
			}
			default:
			{
				iPlayerInput = 0;

				bValidMove = false;
				break;
			}

			}


		}

		if (iMoveCount < 2)
		{
			iMoveCount++;
			//_pGameEngine->SetMoveList(j, '*');
		}
		else
		{
			iMoveCount = 0;

			if (iLocalCount < playerList.size()-1)
			{
				iLocalCount++;
				_pGameEngine->SetMoveList(4, '*');
				_pGameEngine->Draw();
				//_getch();
				_pGameEngine->SetMoveList(5, ' ');
 				_pGameEngine->ResetMoveList();
				
				
			}
			else
			{
				iLocalCount = 0;

				_pGameEngine->Draw();
				//_getch();
				_pGameEngine->ResetMoveList();
				_pGameEngine->SetMoveList(5, ' ');


				_pGameEngine->ChangeState(_pGameEngine->GetExecutingState());
				_pGameEngine->GetExecutingState()->ResetLocalCount();

				system("CLS");

			}
		}
		
	}

}

void CGettingPlayerMovesState::Init()
{

}

void CGettingPlayerMovesState::Cleanup()
{
}

void CGettingPlayerMovesState::Draw(CGameEngine * _pGameEngine)
{
}

void CGettingPlayerMovesState::Step(CGameEngine * _pGameEngine)
{
	ProcessUserInput(_pGameEngine);
}
