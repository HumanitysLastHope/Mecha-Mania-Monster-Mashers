#pragma once
#include "GameState.h"
class CMovingBulletsState : public IGameState
{
public:
	CMovingBulletsState();
	virtual ~CMovingBulletsState();

	// Inherited via IGameState
	virtual void Init() override;
	virtual void Cleanup() override;
	virtual void Draw(CGameEngine * _pGameEngine) override;
	virtual void Step(CGameEngine * _pGameEngine) override;
};

