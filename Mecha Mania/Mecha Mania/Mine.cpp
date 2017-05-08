#include "Mine.h"



CMine::CMine()
{
}


CMine::~CMine()
{
}

TPosition CMine::getPosition()
{
	return m_gridPosition;
}

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