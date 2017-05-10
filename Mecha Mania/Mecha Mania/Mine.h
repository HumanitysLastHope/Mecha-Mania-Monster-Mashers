#include "Movable.h"
#include "Enums.h"
#include "Position.h"
#pragma once

class CMine : public CMovable
{
public:
	CMine(CBoard*, TPosition);
	~CMine();

	TPosition getPosition();
	//void setPosition(TPosition _gridPosition);
	void ArmMine();
	bool isArmed();
	bool Move(EDIRECTION _eDirection);
	void bombBlown();

	//CMine* getMine();

private:

	bool m_isArmed = false;
};

