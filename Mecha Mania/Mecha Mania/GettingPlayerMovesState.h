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

	void ResetZ()
	{
		z = 0;
	}

	int GetI()
	{
		return z;
	}

private:

	int i = 0;
	int j = 0;
	int z = 0;
};

