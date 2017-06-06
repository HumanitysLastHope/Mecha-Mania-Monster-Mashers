#include "Player.h"


CPlayer::CPlayer(TPosition _posMechaGridPosition, EDIRECTION _eMechaFacingDir, CBoard* _pBoard, int _ID) :
	m_Mecha(_posMechaGridPosition, _eMechaFacingDir, _pBoard, _ID)
{

}

CPlayer::~CPlayer()
{
	
}

void CPlayer::SetStartingPos(TPosition _posMechaGridPosition, EDIRECTION _eMechaFacingDir) {
	m_Mecha.SetGridPosition(_posMechaGridPosition);
	m_Mecha.SetMechaFacingDirect(_eMechaFacingDir);
}

CMecha* CPlayer::GetMecha()
{
	return &m_Mecha;
}

std::queue<ECOMMANDS>& CPlayer::GetMoveList()
{
	return m_MoveList;
}

std::vector<char>& CPlayer::GetOutMove()
{
	return m_veccOutMove;
}

bool CPlayer::CheckDeath()
{
	if (this->GetMecha()->GetHealth() < 1)
	{
		m_Mecha.SetDeath(true);
		return true; // Death
	}
	else
	{
		return false;
	}
}

void CPlayer::ResetOutMoves()
{
	while( m_veccOutMove.empty() == false)
	{
		m_veccOutMove.pop_back();
	}
}

