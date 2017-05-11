#pragma once

#include "Movable.h"
#include "Enums.h"
#include "Position.h"

class CBullet : public CMovable
{
public:
	CBullet(CBoard*, const TPosition&, EDIRECTION);
	virtual ~CBullet() override;
	bool Move(EDIRECTION _eDirection);

	EDIRECTION GetDirection();

private:
	EDIRECTION m_eMovingDir;
};

