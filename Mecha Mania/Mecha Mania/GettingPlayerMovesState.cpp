#include "GettingPlayerMovesState.h"
#include "GameEngine.h"
#include <conio.h>

//
//GettingPlayerMovesStates::GettingPlayerMovesStates()
//{
//}
//
//
//GettingPlayerMovesStates::~GettingPlayerMovesStates()
//{
//}

void CGettingPlayerMovesState::ProcessUserInput(CGameEngine _gameEngine)
{
	std::vector<CPlayer> playerList = _gameEngine.GetPlayerList();
	CPlayer playerGetMove = playerList[0];
	int iPlayerInput;
	bool bValidMove = false;

	for (int i = 0; i < _gameEngine.playerAliveCount; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			while (bValidMove == false)
			{
				iPlayerInput = _getch();

				switch (iPlayerInput)
				{
				case 1: // Move sub menu
				{
					iPlayerInput = 0;

					while (bValidMove == false)
					{
						iPlayerInput = _getch();
						bValidMove = true;

						if (iPlayerInput == 1)
						{
							playerList[i].GetMoveList()[j] = MOVEONE;
						}
						else if (iPlayerInput == 2)
						{
							playerList[i].GetMoveList()[j] = MOVETWO;

						}
						else if (iPlayerInput == 3)
						{
							playerList[i].GetMoveList()[j] = MOVETHREE;

						}
						else if (iPlayerInput == 4)
						{
							playerList[i].GetMoveList()[j] = MOVEBACK;

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
						iPlayerInput = _getch();
						bValidMove = true;

						if (iPlayerInput == 1)
						{
							playerList[i].GetMoveList()[j] = ROTATECLOCKWISE;
						}
						else if (iPlayerInput == 2)
						{
							playerList[i].GetMoveList()[j] = ROTATEANTICLOCKWISE;

						}
						else if (iPlayerInput == 3)
						{
							playerList[i].GetMoveList()[j] = FLIP;

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
						iPlayerInput = _getch();
						bValidMove = true;

						if (iPlayerInput == 1)
						{
							playerList[i].GetMoveList()[j] = SHOOT;
						}
						else if (iPlayerInput == 2)
						{
							playerList[i].GetMoveList()[j] = PUSH;

						}
						else if (iPlayerInput == 3)
						{
							playerList[i].GetMoveList()[j] = PLACEMINE;

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


		}
	}
}

void CGettingPlayerMovesState::Init()
{
}

void CGettingPlayerMovesState::Cleanup()
{
}

void CGettingPlayerMovesState::Draw(CGameEngine * _gameEngine)
{
}

void CGettingPlayerMovesState::Step(CGameEngine * _gameEngine)
{
}
