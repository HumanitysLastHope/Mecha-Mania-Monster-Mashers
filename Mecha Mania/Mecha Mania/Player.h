#include "Enums.h"
#include "Mecha.h"
#include <vector>
#include <queue>

#pragma once

class CPlayer
{
public:
	CPlayer(TPosition _posMechaGridPosition, EDIRECTION _eMechaFacingDir, CBoard* _pBoard, int _ID);
	~CPlayer();
	void SetStartingPos(TPosition _posMechaGridPosition, EDIRECTION _eMechaFacingDir);
	CMecha* GetMecha();
	std::queue<ECOMMANDS>& GetMoveList();
	std::vector<char>& GetOutMove();
	bool bDead = false;
	bool CheckDeath();
	void ResetOutMoves();


private:
	int m_iD;
	bool m_bisAlive;
	CMecha m_Mecha;
	std::vector<char> m_veccOutMove;
	std::queue<ECOMMANDS> m_MoveList;
};

