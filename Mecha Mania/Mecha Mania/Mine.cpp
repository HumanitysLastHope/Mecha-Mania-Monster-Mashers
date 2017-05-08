#include "Mine.h"



CMine::CMine()
{
}


CMine::~CMine()
{
}

//CMine* CMine::getMine()
//{
//	return this;
//}

TPosition CMine::getPosition()
{
	return m_gridPosition;
}
//
//void CMine::setPosition(TPosition _gridPosition)
//{
//	m_gridPosition = _gridPosition;
//}

void CMine::ArmMine()
{
	m_isArmed = true;
}

bool CMine::isArmed()
{
	return m_isArmed;
}

void CMine::bombBlown()
{
	delete this;
}