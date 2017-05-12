#include "Bullet.h"
#include "Board.h"
#include "GameEngine.h"

CBullet::CBullet(CBoard* _pBoard, CGameEngine& _rGameEngine, const TPosition& _posGridPosition, EDIRECTION _eMovingDir) :
	m_eMovingDir(_eMovingDir),
	m_rGameEngine(_rGameEngine),
	CMovable(_pBoard, _posGridPosition)
{
}


CBullet::~CBullet()
{
}

bool CBullet::Move(EDIRECTION _eDirection)
{
	TPosition newPos;

	// Get next position that bullet will try to move to
	switch (_eDirection)
	{
	case WEST:
		newPos = { m_posGridPosition.m_iX - 1, m_posGridPosition.m_iY };
		break;
	case NORTH:
		newPos = { m_posGridPosition.m_iX, m_posGridPosition.m_iY - 1 };
		break;
	case EAST:
		newPos = { m_posGridPosition.m_iX + 1, m_posGridPosition.m_iY };
		break;
	case SOUTH:
		newPos = { m_posGridPosition.m_iX, m_posGridPosition.m_iY + 1 };
		break;
	default:
		newPos = { m_posGridPosition.m_iX, m_posGridPosition.m_iY };
		break;
	}

	// Checks if you would hit a wall
	if (newPos.m_iX < 0 || newPos.m_iX >= m_pBoard->GetWidth() || newPos.m_iY < 0 || newPos.m_iY >= m_pBoard->GetHeight())
	{
		m_rGameEngine.DestroyBullet(this);
	}

	// If two bullets collide, destroy both bullets
	else if (m_pBoard->GetTile(newPos).GetBullet() != nullptr)
	{
		CBullet* other = m_pBoard->GetTile(newPos).GetBullet();
		m_rGameEngine.DestroyBullet(this);
		m_rGameEngine.DestroyBullet(other);
	}

	// Otherwise update the bullet to its new position
	else
	{
		m_pBoard->GetTile(m_posGridPosition).SetBullet(nullptr);
		m_pBoard->GetTile(newPos).SetBullet(this);
		m_posGridPosition = newPos;
	}

	return true;
}

EDIRECTION CBullet::GetDirection()
{
	return m_eMovingDir;
}
