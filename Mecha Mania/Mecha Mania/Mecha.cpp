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
	//		if (m_board.GetTile(m_GridPosition.m_iX - 1, m_GridPosition.m_iY).m_pMecha.Move(_eDirection, 1) == true)
	//		{
	//			m_GridPosition.m_iX--;
	//		}
	//	}
	//	break;

	//case NORTH:
	//	if (m_GridPosition.m_iY == 0)
	//		return false;

	//	if (m_board.GetTile(m_GridPosition.m_iX, m_GridPosition.m_iY - 1).m_pMecha != NULL)
	//	{
	//		if (m_board.GetTile(m_GridPosition.m_iX, m_GridPosition.m_iY - 1).m_pMecha.Move(_eDirection, 1) == true)
	//		{
	//			m_GridPosition.m_iY--;
	//		}
	//	}
	//	break;

	//case EAST:
	//	if (m_GridPosition.m_iX == 9)
	//		return false;

	//	if (m_board.GetTile(m_GridPosition.m_iX + 1, m_GridPosition.m_iY).m_pMecha != NULL)
	//	{
	//		if (m_board.GetTile(m_GridPosition.m_iX + 1, m_GridPosition.m_iY).m_pMecha.Move(_eDirection, 1) == true)
	//		{
	//			m_GridPosition.m_iX++;
	//		}
	//	}
	//	break;

	//case SOUTH:
	//	if (m_GridPosition.m_iY == 9)
	//		return false;

	//	if (m_board.GetTile(m_GridPosition.m_iX, m_GridPosition.m_iY + 1).m_pMecha != NULL)
	//	{
	//		if (m_board.GetTile(m_GridPosition.m_iX, m_GridPosition.m_iY + 1).m_pMecha.Move(_eDirection, 1) == true)
	//		{
	//			m_GridPosition.m_iY++;
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
