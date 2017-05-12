#pragma once

#include "Movable.h"
#include "Enums.h"
#include "Position.h"

class CGameEngine;

class CBullet : public CMovable
{
public:
	CBullet(CBoard*, CGameEngine&, const TPosition&, EDIRECTION);
	virtual ~CBullet() override;
	bool Move(EDIRECTION _eDirection);

	EDIRECTION GetDirection();

private:
	EDIRECTION m_eMovingDir;
	CGameEngine& m_rGameEngine;
};

