#include "Board.h"



CBoard::CBoard()
{
}


CBoard::~CBoard()
{
}

CTile& CBoard:: GetTile(int _iX, int _iY) {
	return m_arrMap[_iX][_iY];
}

void CBoard::SetTile(int _iX, int _iY, CTile _pTile) {
	m_arrMap[_iX][_iY] = _pTile;
}