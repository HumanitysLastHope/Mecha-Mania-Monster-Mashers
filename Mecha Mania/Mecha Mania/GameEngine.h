#pragma once

class IGameState;

class CGameEngine
{
public:
	CGameEngine();
	~CGameEngine();

	void Step();
	void Draw();
	void ChangeState(IGameState* _state);
};

