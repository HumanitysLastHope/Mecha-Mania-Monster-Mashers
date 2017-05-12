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
	// Loop over all bullets
	std::vector<CBullet*> vecpBulletList = _pGameEngine->GetBulletList();
	for (auto it = vecpBulletList.begin(); it != vecpBulletList.end(); ++it)
	{
		// Check the bullet hasn't been destroyed
		if (!(*it)->IsDestroyed())
		{
			// Move the bullet
			(*it)->Move((*it)->GetDirection());
		}
	}
}
