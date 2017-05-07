#include "Mecha.h"



CMecha::CMecha()
{
}


CMecha::~CMecha()
{
}

void CMecha::Shoot()
{
}

bool CMecha::Move(EDIRECTION _eDirection, int _iDistance)
{
	//switch (_eDirection)
	//{
	//case WEST:
	//	// Checks if you would hit a wall
	//	if (m_GridPosition.m_iX == 0)
	//		return false;
	//	// If there's a player in front move that player
	//	if (m_board.GetTile(m_GridPosition.m_iX - 1, m_GridPosition.m_iY).m_pMecha != NULL)
	//	{
	//		if (m_board.GetTile(m_GridPosition.m_iX - 1, m_GridPosition.m_iY).m_pMecha.Move(_eDirection, 1) == false)
	//		{
	//			return false;
	//		}
	//	}

	//	m_GridPosition.m_iX--;
	//	if (_iDistance > 1)
	//	{
	//		Move(_eDirection, _iDistance - 1);
	//	}
	//	break;

	//case NORTH:
	//	if (m_GridPosition.m_iY == 0)
	//		return false;

	//	if (m_board.GetTile(m_GridPosition.m_iX, m_GridPosition.m_iY - 1).m_pMecha != NULL)
	//	{
	//		if (m_board.GetTile(m_GridPosition.m_iX, m_GridPosition.m_iY - 1).m_pMecha.Move(_eDirection, 1) == false)
	//		{
	//			return false;
	//		}
	//	}

	//	m_GridPosition.m_iY--;
	//	if (_iDistance > 1)
	//	{
	//		Move(_eDirection, _iDistance - 1);
	//	}
	//	break;

	//case EAST:
	//	if (m_GridPosition.m_iX == 9)
	//		return false;

	//	if (m_board.GetTile(m_GridPosition.m_iX + 1, m_GridPosition.m_iY).m_pMecha != NULL)
	//	{
	//		if (m_board.GetTile(m_GridPosition.m_iX + 1, m_GridPosition.m_iY).m_pMecha.Move(_eDirection, 1) == false)
	//		{
	//			return false;
	//		}
	//	}

	//	m_GridPosition.m_iX++;
	//	if (_iDistance > 1)
	//	{
	//		Move(_eDirection, _iDistance - 1);
	//	}
	//	break;

	//case SOUTH:
	//	if (m_GridPosition.m_iY == 9)
	//		return false;

	//	if (m_board.GetTile(m_GridPosition.m_iX, m_GridPosition.m_iY + 1).m_pMecha != NULL)
	//	{
	//		if (m_board.GetTile(m_GridPosition.m_iX, m_GridPosition.m_iY + 1).m_pMecha.Move(_eDirection, 1) == false)
	//		{
	//			return false;
	//		}

	//		m_GridPosition.m_iY++;
	//		if (_iDistance > 1)
	//		{
	//			Move(_eDirection, _iDistance - 1);
	//		}
	//	}
	//	break;

	//default:
	//	break;
	//}

	return true;
}

void CMecha::Push()
{
}

void CMecha::PlaceMine()
{
}
