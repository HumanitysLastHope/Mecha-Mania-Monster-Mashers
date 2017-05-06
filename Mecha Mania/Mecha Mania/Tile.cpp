#include "Tile.h"



CTile::CTile()
{
}


CTile::~CTile()
{
}

EENVIRONMENT* CTile::GetEnvironment()
{
	return m_peEnvironment;
}

void  CTile::SetEnvironment(EENVIRONMENT* _peEnvironment)
{
	m_peEnvironment = _peEnvironment;
}


CMecha* CTile::GetMecha()
{
	return m_pMecha;
}

void  CTile::SetMecha(CMecha* _pMecha)
{
	m_pMecha = _pMecha;
}