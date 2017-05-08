#include "Position.h"
#pragma once

class CMine
{
public:
	CMine();
	~CMine();

	TPosition getPosition();
	//void setPosition(TPosition _gridPosition);
	void ArmMine();
	bool isArmed();
	void bombBlown();

	//CMine* getMine();

private:

	bool m_isArmed = false;
	TPosition m_gridPosition;
	//CBoard* m_pBoard;
};

