#include "Tile.h"



CTile::CTile()
{
}


CTile::~CTile()
{
}

EENVIRONMENT CTile::GetEnviroment()
{
	return m_peEnvironment;
}

CMecha* CTile::GetMecha()
{
	return m_pMecha;
}
