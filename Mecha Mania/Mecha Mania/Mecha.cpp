#include "Mecha.h"
#include"Board.h"


CMecha::CMecha()
{
}

CMecha::CMecha(TPosition _posGridPosition, EDIRECTION _eFacingDir, CBoard* _pBoard)
	:m_iHealth(5),
	m_posGridPosition(_posGridPosition),
	m_eFacingDir(_eFacingDir),
	m_pBoard(_pBoard)
{
}


CMecha::~CMecha()
{
}

void CMecha::SetGridPosition(TPosition _posGridPosition)
{
	m_posGridPosition = _posGridPosition;
	m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetMecha(this);
}

TPosition CMecha::GetGridPosition() {
	return m_posGridPosition;
}

void CMecha::SetMechaFacingDirect(EDIRECTION _eFacingDir) {
	m_eFacingDir = _eFacingDir;
}

EDIRECTION CMecha::GetMechaFacingDirect() {
	return m_eFacingDir;
}

void CMecha::Shoot()
{
}

bool CMecha::Move(EDIRECTION _eDirection)
{
	switch (_eDirection)
	{
	case WEST:
		// Checks if you would hit a wall
		if (m_posGridPosition.m_iX == 0)
			return false;
		// If there's a player in front move that player
		if (m_pBoard->GetTile(m_posGridPosition.m_iX - 1, m_posGridPosition.m_iY).GetMecha() != nullptr)
		{
			if (m_pBoard->GetTile(m_posGridPosition.m_iX - 1, m_posGridPosition.m_iY).GetMecha()->Move(_eDirection) == false)
			{
				return false;
			}
		}

		m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetMecha(nullptr);
		m_pBoard->GetTile(m_posGridPosition.m_iX - 1, m_posGridPosition.m_iY).SetMecha(this);
		m_posGridPosition.m_iX--;
		break;

	case NORTH:
		if (m_posGridPosition.m_iY == 0)
			return false;

		if (m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY - 1).GetMecha() != nullptr)
		{
			if (m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY - 1).GetMecha()->Move(_eDirection) == false)
			{
				return false;
			}
		}

		m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetMecha(nullptr);
		m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY - 1).SetMecha(this);
		m_posGridPosition.m_iY--;
		break;

	case EAST:
		if (m_posGridPosition.m_iX == 9)
			return false;

		if (m_pBoard->GetTile(m_posGridPosition.m_iX + 1, m_posGridPosition.m_iY).GetMecha() != nullptr)
		{
			if (m_pBoard->GetTile(m_posGridPosition.m_iX + 1, m_posGridPosition.m_iY).GetMecha()->Move(_eDirection) == false)
			{
				return false;
			}
		}

		m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetMecha(nullptr);
		m_pBoard->GetTile(m_posGridPosition.m_iX + 1, m_posGridPosition.m_iY).SetMecha(this);
		m_posGridPosition.m_iX++;
		break;

	case SOUTH:
		if (m_posGridPosition.m_iY == 9)
			return false;

		if (m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY + 1).GetMecha() != nullptr)
		{
			if (m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY + 1).GetMecha()->Move(_eDirection) == false)
			{
				return false;
			}
		}
			m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetMecha(nullptr);
			m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY + 1).SetMecha(this);
			m_posGridPosition.m_iY++;
		
		break;

	default:
		break;
	}

	return true;
}

void CMecha::Rotate(EROTATION _eRotation)
{
	switch (_eRotation)
	{
	case CLOCKWISE: {
		if (GetDirection() == NORTH)
		{
			SetMechaFacingDirect(EAST);
		}
		if (GetDirection() == EAST)
		{
			SetMechaFacingDirect(SOUTH);
		}
		if (GetDirection() == SOUTH)
		{
			SetMechaFacingDirect(WEST);
		}
		if (GetDirection() == WEST)
		{
			SetMechaFacingDirect(NORTH);
		}
	}
	case ANTICLOCKWISE: {
		if (GetDirection() == NORTH)
		{
			SetMechaFacingDirect(WEST);
		}
		if (GetDirection() == EAST)
		{
			SetMechaFacingDirect(NORTH);
		}
		if (GetDirection() == SOUTH)
		{
			SetMechaFacingDirect(EAST);
		}
		if (GetDirection() == WEST)
		{
			SetMechaFacingDirect(SOUTH);
		}
	}
	case ONEEIGHTY: {
		if (GetDirection() == NORTH)
		{
			SetMechaFacingDirect(SOUTH);
		}
		if (GetDirection() == EAST)
		{
			SetMechaFacingDirect(WEST);
		}
		if (GetDirection() == SOUTH)
		{
			SetMechaFacingDirect(NORTH);
		}
		if (GetDirection() == WEST)
		{
			SetMechaFacingDirect(EAST);
		}
	}
	}
}

void CMecha::Push()
{
}

void CMecha::PlaceMine()
{
}

EDIRECTION CMecha::GetDirection()
{
	return m_eFacingDir;
}