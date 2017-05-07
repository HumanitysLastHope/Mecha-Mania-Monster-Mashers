#pragma once
#include "Tile.h"
class CBoard
{
public:
	CBoard();
	~CBoard();

	CTile& GetTile(int _iX, int _iY);
	void SetTile(int _iX, int _iY, CTile* _pTile);

private:
	CTile* m_pMap [10][10];
};

