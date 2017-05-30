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
	bool Move(EDIRECTION _eDirection, CGameEngine* _pGameEngine);
	void Rotate(EROTATION _eRotation);
	CMovable* WhatToPush(CGameEngine* _pGameEngine);
	void PlaceMine();
	EDIRECTION GetDirection();
	int GetHealth() const;
	bool CheckDeath();
	void SetDeath(bool);

	//void ActionText(char _cAction, int _iPlayer, bool _bDied, CGameEngine* _pGameEngine);

private:
	int m_iID;
	EDIRECTION m_eFacingDir;
	int m_iHealth;
	bool m_bDead;
	//CMine m_PlacedMine;
};

