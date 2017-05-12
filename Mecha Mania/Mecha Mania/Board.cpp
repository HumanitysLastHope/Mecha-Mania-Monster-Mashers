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

int CBoard::GetWidth() const
{
	return 10;
}

int CBoard::GetHeight() const
{
	return 10;
}

void CBoard::SetTile(int _iX, int _iY, CTile _pTile) {
	m_arrMap[_iX][_iY] = _pTile;
}

bool CBoard::IsValidPos(const TPosition& _rkpos)
{
	return !(_rkpos.m_iX < 0 || _rkpos.m_iX >= GetWidth() || _rkpos.m_iY < 0 || _rkpos.m_iY >= GetHeight());
}
