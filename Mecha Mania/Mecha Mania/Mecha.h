#pragma once
#include "Position.h"
#include "Enums.h"

class CBoard;
class CMecha
{
public:
	CMecha();
	~CMecha();
	void Shoot();
	bool Move(EDIRECTION _eDirection);
	void Push();
	void PlaceMine();

private:
	int m_iHealth;
	TPosition m_GridPosition;
	EDIRECTION m_eFacingDir;
	//CMine m_PlacedMine;
	CBoard* m_pBoard;
};

