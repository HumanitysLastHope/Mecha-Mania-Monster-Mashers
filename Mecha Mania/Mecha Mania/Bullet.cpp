#include "Bullet.h"
#include "Board.h"

CBullet::CBullet(CBoard* _pBoard, TPosition _posGridPosition) :
	CMovable(_pBoard, _posGridPosition)
{
}


CBullet::~CBullet()
{
}

bool CBullet::Move(EDIRECTION _eDirection)
{
	switch (_eDirection)
	{
	case WEST:
		// Checks if you would hit a wall
		if (m_posGridPosition.m_iX == 0)
		{
			m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetBullet(nullptr);
			return false;
		}
		// If there's a bullet in front move that bullet
		if (m_pBoard->GetTile(m_posGridPosition.m_iX - 1, m_posGridPosition.m_iY).GetBullet() != nullptr)
		{
			// TODO remove bullets from the bullet list
			m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetBullet(nullptr);
			m_pBoard->GetTile(m_posGridPosition.m_iX - 1, m_posGridPosition.m_iY).SetBullet(nullptr);
		}

		m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetBullet(nullptr);
		m_pBoard->GetTile(m_posGridPosition.m_iX - 1, m_posGridPosition.m_iY).SetBullet(this);
		m_posGridPosition.m_iX--;
		break;

	case NORTH:
		if (m_posGridPosition.m_iY == 0)
		{
			m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetBullet(nullptr);
			return false;
		}

		if (m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY - 1).GetBullet() != nullptr)
		{
			// TODO remove bullets from the bullet list
			m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetBullet(nullptr);
			m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY - 1).SetBullet(nullptr);
		}

		m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetBullet(nullptr);
		m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY - 1).SetBullet(this);
		m_posGridPosition.m_iY--;
		break;

	case EAST:
		if (m_posGridPosition.m_iX == 9)
		{
			m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetBullet(nullptr);
			return false;
		}

		if (m_pBoard->GetTile(m_posGridPosition.m_iX + 1, m_posGridPosition.m_iY).GetBullet() != nullptr)
		{
			// TODO remove bullets from the bullet list
			m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetBullet(nullptr);
			m_pBoard->GetTile(m_posGridPosition.m_iX + 1, m_posGridPosition.m_iY).SetBullet(nullptr);
		}

		m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetBullet(nullptr);
		m_pBoard->GetTile(m_posGridPosition.m_iX + 1, m_posGridPosition.m_iY).SetBullet(this);
		m_posGridPosition.m_iX++;
		break;

	case SOUTH:
		if (m_posGridPosition.m_iY == 9)
		{
			m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetBullet(nullptr);
			return false;
		}

		if (m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY + 1).GetBullet() != nullptr)
		{
			// TODO remove bullets from the bullet list
			m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetBullet(nullptr);
			m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY + 1).SetBullet(nullptr);
		}

		m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY).SetBullet(nullptr);
		m_pBoard->GetTile(m_posGridPosition.m_iX, m_posGridPosition.m_iY + 1).SetBullet(this);
		m_posGridPosition.m_iY++;

		break;

	default:
		break;
	}
	return true;
}

EDIRECTION CBullet::GetDirection()
{
	return EDIRECTION();
}
