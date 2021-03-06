#include <iostream>

#include "Mecha.h"
#include "Board.h"
#include "Position.h"
#include "GameEngine.h"
#include "Util.h"
#include <Windows.h>
#include <string>


CMecha::CMecha(TPosition _posGridPosition, EDIRECTION _eFacingDir, CBoard* _pBoard, int _iID)
	:m_iHealth(5),
	m_eFacingDir(_eFacingDir),
	CMovable(_pBoard, _posGridPosition)
{
	m_iID = _iID;
}

CMecha::~CMecha()
{
}

int CMecha::getID()
{
	return m_iID;
}

void CMecha::SetGridPosition(TPosition _posGridPosition)
{
	m_posGridPosition = _posGridPosition;
	m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetMecha(this);
}

TPosition CMecha::GetGridPosition() 
{
	return m_posGridPosition;
}

void CMecha::SetMechaFacingDirect(EDIRECTION _eFacingDir) 
{
	m_eFacingDir = _eFacingDir;
}

EDIRECTION CMecha::GetMechaFacingDirect() 
{
	return m_eFacingDir;
}

void CMecha::ChangeHealth(int _iChangeVal) 
{
	m_iHealth += _iChangeVal;
}

void CMecha::Shoot(CGameEngine& _rGameEngine)
{
	_rGameEngine.SpawnBullet(Util::GetNextPosition(m_posGridPosition, m_eFacingDir), m_eFacingDir);
}

bool CMecha::Move(EDIRECTION _eDirection, CGameEngine* _pGameEngine)
{
	//bool bShunted = false;

	switch (_eDirection)
	{
	case WEST:
		// Checks if you would hit a wall
		if (m_posGridPosition.m_iX == 0)
			return false;
		// If there's a player in front move that player
		if (m_pBoard->GetTile(m_posGridPosition.m_iX - 1, m_posGridPosition.m_iY).GetMecha() != nullptr)
		{
			if (m_pBoard->GetTile(m_posGridPosition.m_iX - 1, m_posGridPosition.m_iY).GetMecha()->Move(_eDirection,_pGameEngine) == false)
			{
				return false;
			}
		}
		
		
		m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetMecha(nullptr);
		m_pBoard->GetTile(m_posGridPosition.m_iX - 1, m_posGridPosition.m_iY).SetMecha(this);
		m_posGridPosition.m_iX--;

		if (m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).GetMine() != nullptr)
		{
			m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).GetMine()->ArmMine();
		}
		
		break;

	case NORTH:
		if (m_posGridPosition.m_iY == 0)
			return false;

		if (m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY - 1).GetMecha() != nullptr)
		{
			if (m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY - 1).GetMecha()->Move(_eDirection, _pGameEngine) == false)
			{
				return false;
			}
		}


		m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetMecha(nullptr);
		m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY - 1).SetMecha(this);
		m_posGridPosition.m_iY--;
		if (m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).GetMine() != nullptr)
		{
			m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).GetMine()->ArmMine();
		}
		break;

	case EAST:
		if (m_posGridPosition.m_iX == 9)
			return false;

		if (m_pBoard->GetTile(m_posGridPosition.m_iX + 1, m_posGridPosition.m_iY).GetMecha() != nullptr)
		{

			if (m_pBoard->GetTile(m_posGridPosition.m_iX + 1, m_posGridPosition.m_iY).GetMecha()->Move(_eDirection, _pGameEngine) == false)
			{
				return false;
			}
		}

		m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetMecha(nullptr);
		m_pBoard->GetTile(m_posGridPosition.m_iX + 1, m_posGridPosition.m_iY).SetMecha(this);
		m_posGridPosition.m_iX++;

		if (m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).GetMine() != nullptr)
		{
			m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).GetMine()->ArmMine();
		}
		break;

	case SOUTH:
		if (m_posGridPosition.m_iY == 9)
			return false;

		if (m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY + 1).GetMecha() != nullptr)
		{

			if (m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY + 1).GetMecha()->Move(_eDirection, _pGameEngine) == false)
			{
				
				return false;
			}
		}

			m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetMecha(nullptr);
			m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY + 1).SetMecha(this);
			m_posGridPosition.m_iY++;
			if (m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).GetMine() != nullptr)
			{
				m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).GetMine()->ArmMine();
			}
		break;

	default:
		break;
	}

	
	if (m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).GetMecha() != nullptr && m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).GetEnvironment() == WATER)// && bShunted == false)
	{
		m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).GetMecha()->m_iHealth--;

		if (m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).GetMecha()->m_iHealth <= 0)
		{
			_pGameEngine->ActionText('W', m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).GetMecha(), true);

		}
		else
		{
			_pGameEngine->ActionText('W', m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).GetMecha(), false);

		}
	}


	if (m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).GetMecha() != nullptr && m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).GetMine() != nullptr)
	{
		if (m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).GetMine()->isArmed() == true)
		{
			m_iHealth = m_iHealth - 2;

			if (m_iHealth <= 0)
			{
				_pGameEngine->ActionText('M', m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).GetMecha(), true);

			}
			else
			{
				_pGameEngine->ActionText('M', m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).GetMecha(), false);

			}
			m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).GetMine()->bombBlown(); // delete the bomb
			m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetMine(nullptr); // set tile to null
		}
		
	}

	return true;
}

void CMecha::Rotate(EROTATION _eRotation)
{
	switch (_eRotation)
	{
	case CLOCKWISE: 
	{
		if (GetDirection() == NORTH)
		{
			SetMechaFacingDirect(EAST);
		}
		else if (GetDirection() == EAST)
		{
			SetMechaFacingDirect(SOUTH);
		}
		else if (GetDirection() == SOUTH)
		{
			SetMechaFacingDirect(WEST);
		}
		else if (GetDirection() == WEST)
		{
			SetMechaFacingDirect(NORTH);
		}
		break;
	}
	case ANTICLOCKWISE: 
	{
		if (GetDirection() == NORTH)
		{
			SetMechaFacingDirect(WEST);
		}
		else if (GetDirection() == EAST)
		{
			SetMechaFacingDirect(NORTH);
		}
		else if (GetDirection() == SOUTH)
		{
			SetMechaFacingDirect(EAST);
		}
		else if (GetDirection() == WEST)
		{
			SetMechaFacingDirect(SOUTH);
		}
		break;
	}
	case ONEEIGHTY: 
	{
		if (GetDirection() == NORTH)
		{
			SetMechaFacingDirect(SOUTH);
		}
		else if (GetDirection() == EAST)
		{
			SetMechaFacingDirect(WEST);
		}
		else if (GetDirection() == SOUTH)
		{
			SetMechaFacingDirect(NORTH);
		}
		else if (GetDirection() == WEST)
		{
			SetMechaFacingDirect(EAST);
		}
		break;
	}
	default:
	{
		break;
	}

	}
}

CMovable* CMecha::WhatToPush(CGameEngine* _pGameEngine)
{
	TPosition posPushPosition = m_posGridPosition;
	switch (m_eFacingDir)
	{
	case WEST:
	{
		while (posPushPosition.m_iX > 0)
		{
			posPushPosition.m_iX--;
			
			if (m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetMecha() != nullptr)
			{
				_pGameEngine->ActionText('S', m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetMecha(), false);
				return m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetMecha();
			}

			if (m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetBullet() != nullptr)
			{
				return m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetBullet();
			}

			if (m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetMine() != nullptr)
			{
				return m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetMine();
			}
		}
	}
		break;

	case NORTH:
	{
		while (posPushPosition.m_iY > 0)
		{
			posPushPosition.m_iY--;

			if (m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetMecha() != nullptr)
			{
				_pGameEngine->ActionText('S', m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetMecha(), false);
				return m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetMecha();
			}

			if (m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetBullet() != nullptr)
			{
				return m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetBullet();
			}

			if (m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetMine() != nullptr)
			{
				return m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetMine();
			}
		}
	}
		break;

	case EAST:
	{
		while (posPushPosition.m_iX < 9)
		{
			posPushPosition.m_iX++;

			if (m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetMecha() != nullptr)
			{
				_pGameEngine->ActionText('S', m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetMecha(), false);
				return m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetMecha();
			}

			if (m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetBullet() != nullptr)
			{
				return m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetBullet();
			}

			if (m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetMine() != nullptr)
			{
				return m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetMine();
			}
		}
	}
		break;

	case SOUTH:
	{
		while (posPushPosition.m_iY < 9)
		{
			posPushPosition.m_iY++;

			if (m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetMecha() != nullptr)
			{
				_pGameEngine->ActionText('S', m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetMecha(), false);
				return m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetMecha();
			}

			if (m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetBullet() != nullptr)
			{
				return m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetBullet();
			}

			if (m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetMine() != nullptr)
			{
				return m_pBoard->GetTile(posPushPosition.m_iX, posPushPosition.m_iY).GetMine();
			}
		}
	}
		break;

	default:
		break;
	}
	return nullptr;
}

void CMecha::PlaceMine()
{
	if (m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).GetMine() == nullptr)
	{
		m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetMine(new CMine(m_pBoard,m_posGridPosition));
	}
}

EDIRECTION CMecha::GetDirection()
{
	return m_eFacingDir;
}

int CMecha::GetHealth() const
{
	return m_iHealth;
}

bool CMecha::CheckDeath()
{
	return m_bDead;
}

void CMecha::SetDeath(bool _isDead)
{
	m_bDead = _isDead;
}
