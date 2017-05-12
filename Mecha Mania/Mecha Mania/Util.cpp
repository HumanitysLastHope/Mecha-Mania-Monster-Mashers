#include "Util.h"
#include "Position.h"

TPosition Util::GetNextPosition(const TPosition & _rkpos, EDIRECTION _eDirection)
{
	TPosition newPos;
	switch (_eDirection)
	{
	case WEST:
		newPos = { _rkpos.m_iX - 1, _rkpos.m_iY };
		break;
	case NORTH:
		newPos = { _rkpos.m_iX, _rkpos.m_iY - 1 };
		break;
	case EAST:
		newPos = { _rkpos.m_iX + 1, _rkpos.m_iY };
		break;
	case SOUTH:
		newPos = { _rkpos.m_iX, _rkpos.m_iY + 1 };
		break;
	case NODIR:
	default:
		newPos = _rkpos;
		break;
	}

	return newPos;
}
