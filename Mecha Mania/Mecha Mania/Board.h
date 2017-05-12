#pragma once
#include <array>
#include "Tile.h"
#include "Position.h"

class CBoard
{
public:
	CBoard();
	~CBoard();

	CTile& GetTile(int _iX, int _iY);
	CTile& GetTile(const TPosition&);
	int GetWidth() const;
	int GetHeight() const;
	void SetTile(int _iX, int _iY, CTile _pTile);

private:
	std::array<std::array<CTile, 10>, 10> m_arrMap;
};

