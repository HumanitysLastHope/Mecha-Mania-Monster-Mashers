#include "Movable.h"
#include "Position.h"

CMovable::CMovable(CBoard* _pBoard, const TPosition& _posGridPosition) :
	m_pBoard(_pBoard),
	m_posGridPosition(_posGridPosition)
{}

CMovable::~CMovable() 
{}

bool CMovable::Move(EDIRECTION)
{
	return false;
}

TPosition CMovable::GetPosition() const
{
	return m_posGridPosition;
}
