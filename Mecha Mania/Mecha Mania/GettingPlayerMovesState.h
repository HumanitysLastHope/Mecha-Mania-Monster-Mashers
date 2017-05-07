#include "GameEngine.h"
#include "Player.h"
#include "GameState.h"

#pragma once

class CGettingPlayerMovesState : public IGameState
{
public:
	
private:

	void ProcessUserInput(CGameEngine _gameEngine);
	

	// Inherited via IGameState
	virtual void Init() override;

	virtual void Cleanup() override;

	virtual void Draw(CGameEngine * _gameEngine) override;

	virtual void Step(CGameEngine * _gameEngine) override;

};

