#include <iostream>
#include <string>
#include <conio.h>

#include "GameEngine.h"

int main()
{
	CGameEngine gameEngine;

	gameEngine.Draw();
	gameEngine.Step();

	_getch();
	return 0;
}