#include "Enums.h"
#include "Mecha.h"
#include <vector>

#pragma once

class CPlayer
{
public:
	CPlayer();
	CPlayer(TPosition _posMechaGridPosition, EDIRECTION _eMechaFacingDir, CBoard* _pBoard);
	~CPlayer();
	CMecha* GetMecha();
	std::vector<ECOMMANDS> GetMoveList();
private:
	int m_iD;
	bool m_bisAlive;
	CMecha m_Mecha;
	std::vector<ECOMMANDS> m_MoveList;
};

