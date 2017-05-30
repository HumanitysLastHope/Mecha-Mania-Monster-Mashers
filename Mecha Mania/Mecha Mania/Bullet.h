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
	bool Move(EDIRECTION _eDirection, CGameEngine* _pGameEngine);

	EDIRECTION GetDirection();
	bool IsDestroyed() const;
	void SetDestroyed();
	int GetDamage() const;

private:
	bool m_bIsDestroyed;
	const int m_iDamage;
	EDIRECTION m_eMovingDir;
	CGameEngine& m_rGameEngine;
};

