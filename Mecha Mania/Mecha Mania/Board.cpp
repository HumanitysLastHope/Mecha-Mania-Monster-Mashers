#include "Board.h"



CBoard::CBoard()
{
}


CBoard::~CBoard()
{
}

CTile& CBoard:: GetTile(int _iX, int _iY) {
	return m_pMap[_iX][_iY];
}