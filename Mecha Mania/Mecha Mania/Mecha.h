#pragma once
#include "Position.h"
#include "Enums.h"

class CBoard;
class CMecha
{
public:
	CMecha();
	CMecha(TPosition _posGridPosition, EDIRECTION _eFacingDir, CBoard* _pBoard);
	~CMecha();
	void Shoot();
	bool Move(EDIRECTION _eDirection);
	void Push();
	void PlaceMine();

private:
	int m_iHealth;
	TPosition m_posGridPosition;
	EDIRECTION m_eFacingDir;
	//CMine m_PlacedMine;
	CBoard* m_pBoard;
};

