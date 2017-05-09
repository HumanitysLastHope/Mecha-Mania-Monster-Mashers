#include "GameEngine.h"
#include "GameState.h"
#include "GettingPlayerMovesState.h"
#include "ExecutingCMDState.h"
#include "Mine.h"
#include <fstream>
#include <iostream>
#include <string>

CGameEngine::CGameEngine() :
	m_Player1({ 0,0 }, NORTH, &m_Level),
	m_Player2({ 0,0 }, NORTH, &m_Level),
	m_Player3({ 0,0 }, NORTH, &m_Level),
	m_Player4({ 0,0 }, NORTH, &m_Level)
{
	LoadBoard(1);
	//std::cout << m_PlayerList[1].GetMecha()->m_posGridPosition.m_iX;
	ChangeState(new CGettingPlayerMovesState);
}


CGameEngine::~CGameEngine()
{
	delete m_pCurGameState;
}

void CGameEngine::Step()
{
	m_pCurGameState->Step(this);
}

bool CGameEngine::CollisionCheck(bool bWaterCheck)
{
	bool _bReturn = false;
	//cycles through the whole grid for each tile and checks and excutes behaviour if a Mecha is standing on water, pit
	for (int _iY = 0; _iY < 10; ++_iY)
	{
		for (int _iX = 0; _iX < 10; ++_iX)
		{
			//checks water
			if (m_Level.GetTile(_iX, _iY).GetEnvironment() == WATER && m_Level.GetTile(_iX, _iY).GetMecha() != nullptr && bWaterCheck == true)
			{
   				m_Level.GetTile(_iX, _iY).GetMecha()->ChangeHealth(-1);
				std::cout << m_Level.GetTile(_iX, _iY).GetMecha()->m_iHealth;

				_bReturn = true;

			}
			//checks pit
			if (m_Level.GetTile(_iX, _iY).GetEnvironment() == PIT && m_Level.GetTile(_iX, _iY).GetMecha() != nullptr)
			{
				m_Level.GetTile(_iX, _iY).GetMecha()->ChangeHealth(-5);
				m_Level.GetTile(_iX, _iY).SetMecha(nullptr);


				//delete m_Level.GetTile(_iX, _iY).GetMecha();
				_bReturn = true;
			}
		}
	}
	return _bReturn;
}

void CGameEngine::WaterCheck(CPlayer* _pPlayer)
{
	if (m_Level.GetTile(_pPlayer->GetMecha()->GetGridPosition().m_iX, _pPlayer->GetMecha()->GetGridPosition().m_iY).GetEnvironment() == WATER)
	{
 		_pPlayer->GetMecha()->ChangeHealth(-1);
		std::cout << _pPlayer->GetMecha()->m_iHealth;

	}
}

void CGameEngine::Draw()
{

	//draws the arena
	for (int _iY = 0; _iY < 10; ++_iY)
	{
		for (int _iX = 0; _iX < 10; ++_iX)
		{
			//draw an empty tile
			if (m_Level.GetTile(_iX, _iY).GetEnvironment() == FLOOR && m_Level.GetTile(_iX, _iY).GetMecha() == nullptr && m_Level.GetTile(_iX, _iY).GetMine() == nullptr)
			{
				char _cEmptyTile = 176;
				std::cout << " " << _cEmptyTile;
			}
			//draw mecha
			if (m_Level.GetTile(_iX, _iY).GetMecha() != nullptr)
			{
				if (m_Level.GetTile(_iX, _iY).GetMecha()->GetDirection() == NORTH)
				{
					char _cMechaImage = 30;
					std::cout << " " << _cMechaImage;
				}
				if (m_Level.GetTile(_iX, _iY).GetMecha()->GetDirection() == EAST)
				{
					char _cMechaImage = 16;
					std::cout << " " << _cMechaImage;
				}
				if (m_Level.GetTile(_iX, _iY).GetMecha()->GetDirection() == SOUTH)
				{
					char _cMechaImage = 31;
					std::cout << " " << _cMechaImage;
				}
				if (m_Level.GetTile(_iX, _iY).GetMecha()->GetDirection() == WEST)
				{
					char _cMechaImage = 17;
					std::cout << " " << _cMechaImage;
				}
			}

			////draw bullet
			else if (m_Level.GetTile(_iX, _iY).GetBullet() != nullptr)
			{
				char _cBulletImage = 249;
				std::cout << " " << _cBulletImage;
			}
			//draw mine
			else if (m_Level.GetTile(_iX, _iY).GetMine() != nullptr)
			{
				char _cMineImage = 15;
				std::cout << " " << _cMineImage;
				m_Level.GetTile(_iX, _iY).GetMine()->ArmMine();
			}

			////draw water
			else if (m_Level.GetTile(_iX, _iY).GetEnvironment() == WATER)
			{
				char _cWaterImage = 126;
				std::cout << " " << _cWaterImage;
			}
			////draw pit
			else if (m_Level.GetTile(_iX, _iY).GetEnvironment() == PIT)
			{
				char _cPitImage = 220;
				std::cout << " " << _cPitImage;
			}

		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
	//m_pCurGameState->Step(this);
}

void CGameEngine::ChangeState(IGameState* _pState)
{
	if (m_pCurGameState != nullptr)
	{
		//std::cout << m_Player1.GetMecha()->m_posGridPosition.m_iX;

		m_pCurGameState->Cleanup();
		delete m_pCurGameState;
	}

	m_pCurGameState = _pState;

	if (_pState != nullptr)
	{
		//std::cout << m_Player1.GetMecha()->m_posGridPosition.m_iX;

		_pState->Init();
	}
}

CBoard& CGameEngine::LoadBoard(int _LevelNum) {

	//m_PlayerList[1]

	if (_LevelNum == 1) {
		//sets the players starting locations and facing direction
		/*m_PlayerList[0].GetMecha()->SetGridPosition({ 1, 2 });
		m_PlayerList[0].GetMecha()->SetMechaFacingDirect(SOUTH);*/
		m_PlayerList[0].GetMecha()->SetGridPosition({ 7, 0 });
		m_PlayerList[0].GetMecha()->SetMechaFacingDirect(SOUTH);

		m_PlayerList[1].GetMecha()->SetGridPosition({ 2, 8 });
		m_PlayerList[1].GetMecha()->SetMechaFacingDirect(EAST);

		m_PlayerList[2].GetMecha()->SetGridPosition({ 7, 1 });
		m_PlayerList[2].GetMecha()->SetMechaFacingDirect(WEST);

		m_PlayerList[3].GetMecha()->SetGridPosition({ 8, 7 });
		m_PlayerList[3].GetMecha()->SetMechaFacingDirect(NORTH);

		//include code here load level 1 from txt file
		std::ifstream levelOneFile;

		levelOneFile.open("LevelOne.txt");
		if (levelOneFile.is_open() == false)
		{
			std::cout << "Error opening file." << std::endl;
		}

		int j = 0;

		for (std::string line; getline(levelOneFile, line); j++)
		{
			for (int i = 0; i < 10; i++)
			{
				switch (line[i])
				{
				case 'p':
				{
					m_Level.GetTile(i, j).SetEnvironment(PIT);
					break;
				}
				case '0':
				{
					break;
				}
				case 'w':
				{
					m_Level.GetTile(i, j).SetEnvironment(WATER);

					break;
				}
				default:
				{
					break;
				}
				}
			}
		}

		//levelOneFile.open("\Mecha - Mania - Monster - Mashers\Mecha Mania\Levels\LevelOne.txt");

		return m_Level;
	}
	if (_LevelNum == 2) {
		//sets the players starting locations and facing direction


		//include code here load level 2 from txt file

		return m_Level;
	}
	if (_LevelNum == 3) {
		//sets the players starting locations and facing direction


		//include code here load level 3 from txt file

		return m_Level;
	}
	else {
		//sets the players starting locations and facing direction


		//include code here load level 4 from txt file

		return m_Level;
	}
}


std::vector<CPlayer>& CGameEngine::GetPlayerList()
{
	return m_PlayerList;
}

void CGameEngine::Run()
{
	CGameEngine gameEngine;

	while (true)
	{
		gameEngine.Draw();
		gameEngine.Step();
		system("CLS");
	}

	_getch();

}