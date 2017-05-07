#pragma once
#include "Tile.h"
class CBoard
{
public:
	CBoard();
	~CBoard();

	CTile& GetTile(int _iX, int _iY);

private:
	CTile m_pMap [100][100];
};

