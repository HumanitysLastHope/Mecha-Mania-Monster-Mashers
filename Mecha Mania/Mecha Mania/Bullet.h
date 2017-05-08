#pragma once

#include "Movable.h"
#include "Enums.h"

class CBullet : public CMovable
{
public:
	CBullet(CBoard*);
	virtual ~CBullet() override;

	EDIRECTION GetDirection();

private:
	EDIRECTION m_eFacingDir;
};

