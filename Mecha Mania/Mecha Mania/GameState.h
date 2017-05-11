#pragma once

class CGameEngine;

class IGameState
{
public:
	virtual ~IGameState();

	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	virtual void Draw(CGameEngine* _gameEngine) = 0;
	virtual void Step(CGameEngine* _gameEngine) = 0;
protected:
	IGameState();
};

