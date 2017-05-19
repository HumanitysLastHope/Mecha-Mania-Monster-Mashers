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
	if (playerList[i].bDead == true)
	{
		if (i < 3)
		{
			i++;
		}
		else
		{
			i = 0;
			_pGameEngine->inGetState = false;
			_pGameEngine->ChangeState(_pGameEngine->GetExecutingState());
		}
	}
	else
	{
		//std::cout << playerList[0].GetMecha()->m_posGridPosition.m_iX;
		CPlayer playerGetMove = playerList[0];
		int iPlayerInput;
		bool bValidMove = false;

		//playerList[0].GetMecha()->SetGridPosition({ 1,1 });

		//for (int i = 0; i < _pGameEngine->playerAliveCount; i++)
		//{

		bValidMove = false;

		while (bValidMove == false)
		{
			iPlayerInput = _getch() - '0';

			switch (iPlayerInput)
			{
			case 1: // Move sub menu
			{
				iPlayerInput = 0;

				while (bValidMove == false)
				{
					iPlayerInput = _getch() - '0';
					bValidMove = true;

					if (iPlayerInput == 1)
					{
						std::cout << "Player " << i << " has selected MOVEONE as their " << j << " move." << std::endl;
						playerList[i].GetMoveList().push(MOVEONE);
					}
					else if (iPlayerInput == 2)
					{
						std::cout << "Player " << i << " has selected MOVETWO as their " << j << " move." << std::endl;

						playerList[i].GetMoveList().push(MOVETWO);

					}
					else if (iPlayerInput == 3)
					{
						std::cout << "Player " << i << " has selected MOVETHREE as their " << j << " move." << std::endl;

						playerList[i].GetMoveList().push(MOVETHREE);

					}
					else if (iPlayerInput == 4)
					{
						std::cout << "Player " << i << " has selected MOVEBACK as their " << j << " move." << std::endl;

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

				while (bValidMove == false)
				{
					iPlayerInput = _getch() - '0';
					bValidMove = true;

					if (iPlayerInput == 1)
					{
						std::cout << "Player " << i << " has selected ROTATECLOCKWISE as their " << j << " move." << std::endl;

						playerList[i].GetMoveList().push(ROTATECLOCKWISE);
					}
					else if (iPlayerInput == 2)
					{
						std::cout << "Player " << i << " has selected ROTATEANTICLOCKWISE as their " << j << " move." << std::endl;

						playerList[i].GetMoveList().push(ROTATEANTICLOCKWISE);

					}
					else if (iPlayerInput == 3)
					{
						std::cout << "Player " << i << " has selected FLIP as their " << j << " move." << std::endl;

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

				while (bValidMove == false)
				{
					iPlayerInput = _getch() - '0';
					bValidMove = true;

					if (iPlayerInput == 1)
					{
						std::cout << "Player " << i << " has selected SHOOT as their " << j << " move." << std::endl;

						playerList[i].GetMoveList().push(SHOOT);
					}
					else if (iPlayerInput == 2)
					{
						std::cout << "Player " << i << " has selected PUSH as their " << j << " move." << std::endl;

						playerList[i].GetMoveList().push(PUSH);

					}
					else if (iPlayerInput == 3)
					{
						std::cout << "Player " << i << " has selected PLACEMINE as their " << j << " move." << std::endl;

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
		}
		else
		{
			j = 0;
			if (i < 3)
			{
				i++;
			}
			else
			{
				i = 0;
				_pGameEngine->ChangeState(_pGameEngine->GetExecutingState());
				_pGameEngine->GetExecutingState()->ResetZ();
			}
		}
		std::cout << "Press any key to continue..." << std::endl;
		_getch();
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
