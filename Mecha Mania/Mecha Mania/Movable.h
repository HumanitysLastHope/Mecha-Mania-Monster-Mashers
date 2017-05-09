#pragma once

#include "Enums.h"
#include "Position.h"
class CBoard;

class CMovable
{
public:
	CMovable(CBoard*, TPosition);
	virtual ~CMovable();

	virtual bool Move(EDIRECTION) = 0;
	TPosition GetPosition();

protected:
	TPosition m_posGridPosition;
	CBoard*   m_pBoard;
};