#include "GameEngine.h"
#include "GettingPlayerMovesState.h"
#include <conio.h>

int main()
{
	CGameEngine gameEngine;

	gameEngine.Draw();
	//gameEngine.Step();

	_getch();
	return 0;
}