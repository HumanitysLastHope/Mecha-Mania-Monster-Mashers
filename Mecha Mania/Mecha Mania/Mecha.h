#pragma once
#include "Position.h"
#include "Enums.h"

class CBoard;
class CBullet;	// TODO:Include this
class CMine;	// TODO:Include this
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
	void ChangeHealth(int _iChangeVal);

	void Shoot();
	bool Move(EDIRECTION _eDirection);
	void Rotate(EROTATION _eRotation);
	void WhatToPush(CBullet* _pbulBullet, CMine* _pminMine, CMecha* _pmecMecha);
	void PlaceMine();
	EDIRECTION GetDirection();

	int m_iHealth;



private:
	
	EDIRECTION m_eFacingDir;
	//CMine m_PlacedMine;
	CBoard* m_pBoard;
	TPosition m_posGridPosition;
};

