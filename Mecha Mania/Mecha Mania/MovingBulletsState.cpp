#include "MovingBulletsState.h"
#include "GameEngine.h"
#include "Bullet.h"
#include "Tile.h"

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
	// Move all bullets
	std::vector<CBullet*> vecpBullets = _pGameEngine->GetBulletList();
	for (auto it = vecpBullets.begin(); it != vecpBullets.end(); ++it)
	{
		// Check the bullet hasn't been destroyed
		if (!(*it)->IsDestroyed())
		{
			// Move the bullet 
			// (destroys bullets that try to phase through each other,
			// all others collisions are handled in the collision check at the end of 
			// this step)
			(*it)->Move((*it)->GetDirection());
		}
	}
}
