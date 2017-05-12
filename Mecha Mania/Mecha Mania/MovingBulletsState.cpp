#include "MovingBulletsState.h"
#include "GameEngine.h"
#include "Bullet.h"

CMovingBulletsState::CMovingBulletsState()
{
}


CMovingBulletsState::~CMovingBulletsState()
{
}

void CMovingBulletsState::Init()
{
}

void CMovingBulletsState::Cleanup()
{
}

void CMovingBulletsState::Draw(CGameEngine * _pGameEngine)
{

}

void CMovingBulletsState::Step(CGameEngine * _pGameEngine)
{
	static int iBulletIdx = 0;
	std::vector<CBullet*> vecpBulletList = _pGameEngine->GetBulletList();

	// Check we have bullets to move
	if (vecpBulletList.size() > 0)
	{
		// Check we have a valid index into the bullet list
		if (iBulletIdx >= vecpBulletList.size())
		{
			iBulletIdx = 0;
		}

		// Move one bullet one space
		CBullet* pBullet = vecpBulletList.at(iBulletIdx);
		pBullet->Move(pBullet->GetDirection());

		// Update the index to the next bullet to be moved
		iBulletIdx = (iBulletIdx + 1) % vecpBulletList.size();
	}
}
