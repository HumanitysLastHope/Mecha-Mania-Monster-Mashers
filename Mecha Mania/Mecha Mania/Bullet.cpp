#include "Bullet.h"
#include "Board.h"
#include "GameEngine.h"

CBullet::CBullet(CBoard* _pBoard, CGameEngine& _rGameEngine, const TPosition& _posGridPosition, EDIRECTION _eMovingDir) :
	m_eMovingDir(_eMovingDir),
	m_rGameEngine(_rGameEngine),
	m_bIsDestroyed(false),
	CMovable(_pBoard, _posGridPosition)
{
}


CBullet::~CBullet()
{
}

TPosition GetNextPosition(const TPosition& _rkpos, EDIRECTION _eDirection)
{
	TPosition newPos;
	switch (_eDirection)
	{
	case WEST:
		newPos = { _rkpos.m_iX - 1, _rkpos.m_iY };
		break;
	case NORTH:
		newPos = { _rkpos.m_iX, _rkpos.m_iY - 1 };
		break;
	case EAST:
		newPos = { _rkpos.m_iX + 1, _rkpos.m_iY };
		break;
	case SOUTH:
		newPos = { _rkpos.m_iX, _rkpos.m_iY + 1 };
		break;
	case NODIR:
	default:
		newPos = _rkpos;
		break;
	}

	return newPos;
}

std::vector<CBullet*> CBullet::GetIncomingBullets(const TPosition & _rkpos)
{
	std::vector<CBullet*> vecpIncomingBullets;

	// Loop over cardinal directions
	for (int iDir = 0; iDir != EDIRECTION::NODIR; ++iDir)
	{
		TPosition curCardinalPos = GetNextPosition(_rkpos, static_cast<EDIRECTION>(iDir));

		// Check position is valid
		if (m_pBoard->IsValidPos(curCardinalPos))
		{
			// Check if cardinal positions contain bullets
			CBullet* pBullet = m_pBoard->GetTile(curCardinalPos).GetBullet();
			if (pBullet)
			{
				// Check if bullets will intersect after next step
				TPosition nextpos = GetNextPosition(pBullet->GetPosition(), pBullet->GetDirection());
				if (nextpos == _rkpos)
				{
					vecpIncomingBullets.push_back(pBullet);
				}
			}
		}
	}

	return vecpIncomingBullets;
}

bool CBullet::Move(EDIRECTION _eDirection)
{
	// Get next position that bullet will try to move to
	TPosition newPos = GetNextPosition(m_posGridPosition, _eDirection);

	// Checks if you would hit a wall
	if (!m_pBoard->IsValidPos(newPos))
	{
		m_rGameEngine.DestroyBullet(this);
		return true;
	}

	// Handle case where two bullets phase through each other in one step
	bool bCollision = false;
	if (m_pBoard->GetTile(newPos).GetBullet() != nullptr)
	{
		CBullet* other = m_pBoard->GetTile(newPos).GetBullet();

		// Get other bullets next position
		TPosition otherNewPos = GetNextPosition(other->GetPosition(), other->GetDirection());

		// Collision case when both bullets try to pass through each other
		if (newPos == other->GetPosition() && otherNewPos == m_posGridPosition)
		{
			bCollision = true;
		}

		// Destroy colliding bullets
		if (bCollision)
		{
			m_rGameEngine.DestroyBullet(this);
			m_rGameEngine.DestroyBullet(other);
		}
	}

	// Handle case where bullets will overlap after step
	std::vector<CBullet*> vecpIncomingBullets = GetIncomingBullets(newPos);
	if (vecpIncomingBullets.size() >= 2)
	{
		bCollision = true;
		for (auto it = vecpIncomingBullets.begin(); it != vecpIncomingBullets.end(); ++it)
		{
			m_rGameEngine.DestroyBullet(*it);
		}
	}

	// If bullets aren't colliding, then move this bullet to the next tile
	if (!bCollision)
	{
		m_pBoard->GetTile(m_posGridPosition).RemoveBullet(this);
		m_pBoard->GetTile(newPos).AddBullet(this);
		m_posGridPosition = newPos;
	}

	return true;
}

EDIRECTION CBullet::GetDirection()
{
	return m_eMovingDir;
}

bool CBullet::IsDestroyed() const
{
	return m_bIsDestroyed;
}

void CBullet::SetDestroyed()
{
	m_bIsDestroyed = true;
}
