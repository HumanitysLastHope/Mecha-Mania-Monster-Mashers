#include "Player.h"

CPlayer::CPlayer()
{
	
}

CPlayer::CPlayer(TPosition _posMechaGridPosition, EDIRECTION _eMechaFacingDir, CBoard* _pBoard):
	m_Mecha(_posMechaGridPosition, _eMechaFacingDir, _pBoard)
{
}

CPlayer::~CPlayer()
{
}

CMecha* CPlayer::GetMecha()
{
	return &m_Mecha;
}

std::vector<ECOMMANDS> CPlayer::GetMoveList()
{
	return m_MoveList;
}
