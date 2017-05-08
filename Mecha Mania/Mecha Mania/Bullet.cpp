#include "Bullet.h"

CBullet::CBullet(CBoard* _pBoard) :
	CMovable(_pBoard)
{
}


CBullet::~CBullet()
{
}

EDIRECTION CBullet::GetDirection()
{
	return EDIRECTION();
}
