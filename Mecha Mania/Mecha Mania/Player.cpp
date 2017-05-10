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

bool CPlayer::CheckDeath()
{
	if (this->GetMecha()->m_iHealth < 1)
	{
		return true; // Death
	}
	else
	{
		return false;
	}
}