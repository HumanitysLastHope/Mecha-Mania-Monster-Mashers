#include "Bullet.h"

CBullet::CBullet(CBoard* _pBoard, TPosition _posGridPosition) :
	CMovable(_pBoard, _posGridPosition)
{
}


CBullet::~CBullet()
{
}

EDIRECTION CBullet::GetDirection()
{
	return EDIRECTION();
}
