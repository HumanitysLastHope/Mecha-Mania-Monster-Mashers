#pragma once

#include "Movable.h"
#include "Enums.h"
#include "Position.h"

class CBullet : public CMovable
{
public:
	CBullet(CBoard*, TPosition);
	virtual ~CBullet() override;

	EDIRECTION GetDirection();

private:
	EDIRECTION m_eFacingDir;
};

