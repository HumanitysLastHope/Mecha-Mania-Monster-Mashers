#pragma once
#include "Position.h"
#include "Enums.h"
#include "Movable.h"

class CBoard;
class CBullet;	// TODO:Include this
class CMine;	// TODO:Include this
class CMecha: public CMovable
{
public:
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
	CMovable* WhatToPush();
	void PlaceMine();
	EDIRECTION GetDirection();

	int m_iHealth;



private:
	
	EDIRECTION m_eFacingDir;
	//CMine m_PlacedMine;
};

