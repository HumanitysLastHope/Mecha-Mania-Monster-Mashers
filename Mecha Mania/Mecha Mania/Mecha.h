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
	CMecha(TPosition _posGridPosition, EDIRECTION _eFacingDir, CBoard* _pBoard, int _iID);
	~CMecha();

	int getID();
	void setID(int _iID);
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

	//THIS SHOULD BE PRIVATE!!!!!!!!!!!
	int m_iHealth;



private:
	int m_iID;
	EDIRECTION m_eFacingDir;
	//CMine m_PlacedMine;
};

