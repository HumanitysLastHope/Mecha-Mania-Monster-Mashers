#include "Bullet.h"
#include "Board.h"
#include "GameEngine.h"
#include "Util.h"

CBullet::CBullet(CBoard* _pBoard, CGameEngine& _rGameEngine, const TPosition& _posGridPosition, EDIRECTION _eMovingDir) :
	m_eMovingDir(_eMovingDir),
	m_rGameEngine(_rGameEngine),
	m_bIsDestroyed(false),
	m_iDamage(1),
	CMovable(_pBoard, _posGridPosition)
{
}


CBullet::~CBullet()
{
}

bool CBullet::Move(EDIRECTION _eDirection, CGameEngine* _pGameEngine)
{
	// Get next position that bullet will try to move to
	TPosition newPos = Util::GetNextPosition(m_posGridPosition, _eDirection);

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
		TPosition otherNewPos = Util::GetNextPosition(other->GetPosition(), other->GetDirection());

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

	// If bullets aren't phasing through each other, then move this bullet to the next tile
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

int CBullet::GetDamage() const
{
	return m_iDamage;
}
