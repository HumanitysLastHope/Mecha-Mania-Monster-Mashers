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

	void SetGridPosition(TPosition _posGridPosition);
	TPosition GetGridPosition();
	void SetMechaFacingDirect(EDIRECTION _eFacingDir);
	EDIRECTION GetMechaFacingDirect();

	void Shoot();
	bool Move(EDIRECTION _eDirection);
	void Rotate(EROTATION _eRotation);
	void Push();
	void PlaceMine();
	EDIRECTION GetDirection();


private:
	int m_iHealth;
	TPosition m_posGridPosition;
	EDIRECTION m_eFacingDir;
	//CMine m_PlacedMine;
	CBoard* m_pBoard;
};

