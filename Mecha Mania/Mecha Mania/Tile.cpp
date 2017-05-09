#include "Tile.h"


CTile::CTile()
{
	m_peEnvironment = FLOOR;
}


CTile::~CTile()
{
}

EENVIRONMENT CTile::GetEnvironment()
{
	return m_peEnvironment;
}

void  CTile::SetEnvironment(EENVIRONMENT _peEnvironment)
{
	m_peEnvironment = _peEnvironment;
}


CMecha* CTile::GetMecha()
{
	return m_pMecha;
}

CMine* CTile::GetMine()
{
	return m_pMine;
}

CBullet* CTile::GetBullet()
{
	return m_pBullet;
}

void CTile::SetMecha(CMecha* _pMecha)
{
	m_pMecha = _pMecha;
}

void CTile::SetMine(CMine* _pMine)
{
	m_pMine = _pMine;
}

void CTile::SetBullet(CBullet* _pBullet)
{
	m_pBullet = _pBullet;
}