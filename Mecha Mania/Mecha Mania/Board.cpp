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

CTile & CBoard::GetTile(const TPosition& _pos)
{
	return m_arrMap[_pos.m_iX][_pos.m_iY];
}

void CBoard::SetTile(int _iX, int _iY, CTile _pTile) {
	m_arrMap[_iX][_iY] = _pTile;
}