#pragma once
#include "Position.h"
#include "Enums.h"
#include "Board.h"

class CMecha
{
public:
	CMecha();
	~CMecha();
	void Shoot();
	bool Move(EDIRECTION _eDirection, int _iDistance);
	void Push();
	void PlaceMine();
	void MovedOnto();

private:
	int m_iHealth;
	TPosition m_GridPosition;
	EDIRECTION m_eFacingDir;
	//CMine m_PlacedMine;
	CBoard m_board;
};

