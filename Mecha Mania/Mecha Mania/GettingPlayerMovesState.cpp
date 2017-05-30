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

				while (bValidMove == false)
				{
					iPlayerInput = _getch() - '0';
					bValidMove = true;


					if (iPlayerInput == 1)
					{
						_pGameEngine->SetMoveList(j * 2 + 1, '*');
						playerList[i].GetMoveList().push(MOVEONE);
					}
					else if (iPlayerInput == 2)
					{
						_pGameEngine->SetMoveList(j * 2 + 1, '*');
						playerList[i].GetMoveList().push(MOVETWO);

					}
					else if (iPlayerInput == 3)
					{
						_pGameEngine->SetMoveList(j * 2 + 1, '*');
						playerList[i].GetMoveList().push(MOVETHREE);

					}
					else if (iPlayerInput == 4)
					{
						_pGameEngine->SetMoveList(j * 2 + 1, '*');
						playerList[i].GetMoveList().push(MOVEBACK);

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

				while (bValidMove == false)
				{
					iPlayerInput = _getch() - '0';
					bValidMove = true;

					if (iPlayerInput == 1)
					{
						_pGameEngine->SetMoveList(j * 2 + 1, '*');
						playerList[i].GetMoveList().push(ROTATECLOCKWISE);
					}
					else if (iPlayerInput == 2)
					{
						_pGameEngine->SetMoveList(j * 2 + 1, '*');
						playerList[i].GetMoveList().push(ROTATEANTICLOCKWISE);

					}
					else if (iPlayerInput == 3)
					{
						_pGameEngine->SetMoveList(j * 2 + 1, '*');
						playerList[i].GetMoveList().push(FLIP);

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

				while (bValidMove == false)
				{
					iPlayerInput = _getch() - '0';
					bValidMove = true;

					

					if (iPlayerInput == 1)
					{
						_pGameEngine->SetMoveList(j * 2 + 1, '*');
						playerList[i].GetMoveList().push(SHOOT);
					}
					else if (iPlayerInput == 2)
					{
						_pGameEngine->SetMoveList(j * 2 + 1, '*');
						playerList[i].GetMoveList().push(PUSH);

					}
					else if (iPlayerInput == 3)
					{
						_pGameEngine->SetMoveList(j * 2 + 1, '*');
						playerList[i].GetMoveList().push(PLACEMINE);

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
