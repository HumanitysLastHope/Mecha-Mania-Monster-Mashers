#include "GameEngine.h"
#include "Player.h"
#include "GameState.h"

#pragma once

class CGettingPlayerMovesState : public IGameState
{
public:
	CGettingPlayerMovesState();
	virtual ~CGettingPlayerMovesState() override;

	void ProcessUserInput(CGameEngine* _pGameEngine);
	

	// Inherited via IGameState
	virtual void Init() override;

	virtual void Cleanup() override;

	virtual void Draw(CGameEngine * _pGameEngine) override;

	virtual void Step(CGameEngine * _pGameEngine) override;

};

