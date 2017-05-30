#pragma once

#include "Enums.h"
#include "Position.h"
//#include "GameEngine.h"
class CBoard;
class CGameEngine;

class CMovable
{
public:
	CMovable(CBoard*, const TPosition&);
	virtual ~CMovable();

	virtual bool Move(EDIRECTION, CGameEngine*) = 0;
	TPosition GetPosition() const;

protected:
	TPosition m_posGridPosition;
	CBoard*   m_pBoard;
};