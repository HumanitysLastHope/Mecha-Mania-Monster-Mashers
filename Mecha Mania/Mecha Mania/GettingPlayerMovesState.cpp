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
	i = 0;
	j = 0;
}

CGettingPlayerMovesState::~CGettingPlayerMovesState()
{
}

void CGettingPlayerMovesState::ProcessUserInput(CGameEngine* _pGameEngine)
{
	std::vector<CPlayer>& playerList = _pGameEngine->GetPlayerList();

	i = _pGameEngine->m_CommandOrder[z];

	if (playerList[i].bDead == true)
	{
		if (i < playerList.size()-1 && z< playerList.size() - 1)
		{
			i++;
			z++;
			

		}
		else
		{
			i = 0;
			z = 0;
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

				_pGameEngine->SetMoveList(j * 2, '*');
				_pGameEngine->Draw();

				playerList[i].GetOutMove().push_back('1');

				while (bValidMove == false)
				{
					iPlayerInput = _getch() - '0';
					bValidMove = true;


					if (iPlayerInput == 1)
					{
						_pGameEngine->SetMoveList(j * 2 + 1, '*');
						playerList[i].GetMoveList().push(MOVEONE);
						playerList[i].GetOutMove().push_back('1');

					}
					else if (iPlayerInput == 2)
					{
						_pGameEngine->SetMoveList(j * 2 + 1, '*');
						playerList[i].GetMoveList().push(MOVETWO);
						playerList[i].GetOutMove().push_back('2');


					}
					else if (iPlayerInput == 3)
					{
						_pGameEngine->SetMoveList(j * 2 + 1, '*');
						playerList[i].GetMoveList().push(MOVETHREE);
						playerList[i].GetOutMove().push_back('3');


					}
					else if (iPlayerInput == 4)
					{
						_pGameEngine->SetMoveList(j * 2 + 1, '*');
						playerList[i].GetMoveList().push(MOVEBACK);
						playerList[i].GetOutMove().push_back('4');


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
				_pGameEngine->SetMoveList(j * 2, '*');
				_pGameEngine->Draw();
				playerList[i].GetOutMove().push_back('2');


				while (bValidMove == false)
				{
					iPlayerInput = _getch() - '0';
					bValidMove = true;

					if (iPlayerInput == 1)
					{
						_pGameEngine->SetMoveList(j * 2 + 1, '*');
						playerList[i].GetMoveList().push(ROTATECLOCKWISE);
						playerList[i].GetOutMove().push_back('1');

					}
					else if (iPlayerInput == 2)
					{
						_pGameEngine->SetMoveList(j * 2 + 1, '*');
						playerList[i].GetMoveList().push(ROTATEANTICLOCKWISE);
						playerList[i].GetOutMove().push_back('2');


					}
					else if (iPlayerInput == 3)
					{
						_pGameEngine->SetMoveList(j * 2 + 1, '*');
						playerList[i].GetMoveList().push(FLIP);
						playerList[i].GetOutMove().push_back('3');


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
				_pGameEngine->SetMoveList(j * 2, '*');
				_pGameEngine->Draw();

				playerList[i].GetOutMove().push_back('3');


				while (bValidMove == false)
				{
					iPlayerInput = _getch() - '0';
					bValidMove = true;

					

					if (iPlayerInput == 1)
					{
						_pGameEngine->SetMoveList(j * 2 + 1, '*');
						playerList[i].GetMoveList().push(SHOOT);
						playerList[i].GetOutMove().push_back('1');

					}
					else if (iPlayerInput == 2)
					{
						_pGameEngine->SetMoveList(j * 2 + 1, '*');
						playerList[i].GetMoveList().push(PUSH);
						playerList[i].GetOutMove().push_back('2');


					}
					else if (iPlayerInput == 3)
					{
						_pGameEngine->SetMoveList(j * 2 + 1, '*');
						playerList[i].GetMoveList().push(PLACEMINE);
						playerList[i].GetOutMove().push_back('3');


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

		if (j < 2)
		{
			j++;
			//_pGameEngine->SetMoveList(j, '*');
		}
		else
		{
			j = 0;

			if (z < playerList.size()-1)
			{
				z++;
				_pGameEngine->SetMoveList(4, '*');
				_pGameEngine->Draw();
				//_getch();
				_pGameEngine->SetMoveList(5, ' ');
 				_pGameEngine->ResetMoveList();
				
				
			}
			else
			{
				z = 0;

				_pGameEngine->Draw();
				//_getch();
				_pGameEngine->ResetMoveList();
				_pGameEngine->SetMoveList(5, ' ');


				_pGameEngine->ChangeState(_pGameEngine->GetExecutingState());
				_pGameEngine->GetExecutingState()->ResetZ();

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
