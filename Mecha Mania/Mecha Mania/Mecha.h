#pragma once
#include "Position.h"
#include "Enums.h"
#include "Movable.h"

class CGameEngine;
class CBoard;
class CBullet;	// TODO:Include this
class CMine;	// TODO:Include this
class CMecha: public CMovable
{
public:
	CMecha(TPosition _posGridPosition, EDIRECTION _eFacingDir, CBoard* _pBoard, int _iID);
	~CMecha();

	int getID();
	void SetGridPosition(TPosition _posGridPosition);
	TPosition GetGridPosition();
	void SetMechaFacingDirect(EDIRECTION _eFacingDir);
	EDIRECTION GetMechaFacingDirect();
	void ChangeHealth(int _iChangeVal);

	void Shoot(CGameEngine& _rGameEngine);
	bool Move(EDIRECTION _eDirection);
	void Rotate(EROTATION _eRotation);
	CMovable* WhatToPush();
	void PlaceMine();
	EDIRECTION GetDirection();
	int GetHealth() const;

	void ActionText(char _cAction, int _iPlayer, bool _bDied);

	void GotoXY(int _iX, int _iY);


private:
	int m_iID;
	EDIRECTION m_eFacingDir;
	int m_iHealth;
	//CMine m_PlacedMine;
};

