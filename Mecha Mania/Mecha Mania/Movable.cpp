#include "Movable.h"

CMovable::CMovable(CBoard* _pBoard) : 
	m_pBoard(_pBoard) 
{}

CMovable::~CMovable() 
{}

bool CMovable::Move(EDIRECTION)
{
	return false;
}

TPosition CMovable::GetPosition()
{
	return m_posBoardPos;
}
