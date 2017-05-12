#pragma once

#include <vector>

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
	bool IsDestroyed() const;
	void SetDestroyed();

private:
	bool m_bIsDestroyed;

	EDIRECTION m_eMovingDir;
	CGameEngine& m_rGameEngine;
};

