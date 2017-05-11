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
	std::vector<CBullet*> vecpBulletList = _pGameEngine->GetBulletList();
	if (vecpBulletList.size() > 0)
	{
		static int iBulletIdx = 0;
		if (iBulletIdx >= vecpBulletList.size())
		{
			iBulletIdx = 0;
		}

		CBullet* pBullet = vecpBulletList.at(iBulletIdx);
		pBullet->Move(pBullet->GetDirection());

		iBulletIdx = (iBulletIdx + 1) % vecpBulletList.size();
	}
}
