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
	void SetStartingPos(TPosition _posMechaGridPosition, EDIRECTION _eMechaFacingDir);
	CMecha* GetMecha();
	std::vector<ECOMMANDS> GetMoveList();
	void SetMoveList(std::vector<ECOMMANDS> PlayerMoveList);
private:
	int m_iD;
	bool m_bisAlive;
	CMecha m_Mecha;
	std::vector<ECOMMANDS> m_MoveList;
};

