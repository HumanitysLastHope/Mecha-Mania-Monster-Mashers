#pragma once

#include <Windows.h>
#include "Enums.h"

struct TPosition;

namespace Util
{
	TPosition GetNextPosition(const TPosition& _rkpos, EDIRECTION _eDirection);
	
}

inline void GotoXY(int _iX, int _iY) {
	COORD point;
	point.X = _iX;
	point.Y = _iY;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}