#include "GameEngine.h"
#include "Player.h"
#include "GameState.h"

#pragma once
class ExecutingCMDState : public IGameState
{
public:
	ExecutingCMDState();
	virtual ~ExecutingCMDState() override;

	void ExecuteUserInput(CGameEngine* _pGameEngine, int i);


	// Inherited via IGameState
	virtual void Init() override;

	virtual void Cleanup() override;

	virtual void Draw(CGameEngine * _pGameEngine) override;

	virtual void Step(CGameEngine * _pGameEngine) override;
};

