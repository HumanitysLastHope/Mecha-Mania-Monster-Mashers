#pragma once

#include "IGameState.h"

class CGameEngine
{
public:
	CGameEngine();
	~CGameEngine();

	void Step();
	void Draw();
	void ChangeState(IGameState* _state);
};

