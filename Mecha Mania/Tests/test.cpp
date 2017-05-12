#include <conio.h>

#include <GameEngine.h>
#include <MovingBulletsState.h>
#include <Position.h>
#include <Enums.h>

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

int main(int argc, char* argv[])
{
	// global setup...

	int result = Catch::Session().run(argc, argv);

	// global clean-up...

	_getch();

	return (result < 0xff ? result : 0xff);
}

TEST_CASE("Test Bullet Movement")
{
	// Init game engine
	CGameEngine gameEngine;

	// Add some bullets
	CBullet* pBullet1 = gameEngine.SpawnBullet({ 0, 0 }, EDIRECTION::EAST);
	CBullet* pBullet2 = gameEngine.SpawnBullet({ 1, 0 }, EDIRECTION::SOUTH);
	CBullet* pBullet3 = gameEngine.SpawnBullet({ 1, 1 }, EDIRECTION::WEST);
	CBullet* pBullet4 = gameEngine.SpawnBullet({ 0, 1 }, EDIRECTION::NORTH);

	// Swap current system to the moving bullets system
	CMovingBulletsState* pState = new CMovingBulletsState;
	gameEngine.ChangeState(pState);

	// Run one step
	gameEngine.Step();

	// Check bullets move appropriately
	REQUIRE(pBullet1->GetPosition().m_iX == 1);
	REQUIRE(pBullet1->GetPosition().m_iY == 0);
	REQUIRE(gameEngine.GetBoard().GetTile(1, 0).GetBullet() == pBullet1);

	REQUIRE(pBullet2->GetPosition().m_iX == 1);
	REQUIRE(pBullet2->GetPosition().m_iY == 1);
	REQUIRE(gameEngine.GetBoard().GetTile(1, 1).GetBullet() == pBullet2);

	REQUIRE(pBullet3->GetPosition().m_iX == 0);
	REQUIRE(pBullet3->GetPosition().m_iY == 1);
	REQUIRE(gameEngine.GetBoard().GetTile(0, 1).GetBullet() == pBullet3);

	REQUIRE(pBullet4->GetPosition().m_iX == 0);
	REQUIRE(pBullet4->GetPosition().m_iY == 0);
	REQUIRE(gameEngine.GetBoard().GetTile(0, 0).GetBullet() == pBullet4);
}

TEST_CASE("Test spawning bullet ontop of existing bullet")
{
	// Init game engine
	CGameEngine gameEngine;

	// Add some bullets
	CBullet* pBullet1 = gameEngine.SpawnBullet({ 0, 0 }, EDIRECTION::EAST);
	CBullet* pBullet2 = gameEngine.SpawnBullet({ 0, 0 }, EDIRECTION::SOUTH);
	CBullet* pBullet3 = gameEngine.SpawnBullet({ 2, 0 }, EDIRECTION::WEST);
	CBullet* pBullet4 = gameEngine.SpawnBullet({ 0, 2 }, EDIRECTION::NORTH);

	REQUIRE(pBullet1->IsDestroyed());
	// REQUIRE(pBullet2->IsDestroyed()); <------ Never created

	// Swap current system to the moving bullets system
	CMovingBulletsState* pState = new CMovingBulletsState;
	gameEngine.ChangeState(pState);

	// Run one step
	gameEngine.Step();

	// Check that appropriate bullets are destroyed
	REQUIRE(gameEngine.GetBoard().GetTile(0, 0).GetBullet() == nullptr);
	REQUIRE(gameEngine.GetBoard().GetTile(1, 0).GetBullet() == pBullet3);
	REQUIRE(gameEngine.GetBoard().GetTile(0, 1).GetBullet() == pBullet4);
}

TEST_CASE("Test bullets colliding")
{
	// Init game engine
	CGameEngine gameEngine;

	std::vector<CBullet*>& rvecpBullets = gameEngine.GetBulletList();
	CBoard& rBoard = gameEngine.GetBoard();

	// Directly colliding bullets adjacent to each other
	CBullet* pBullet1 = gameEngine.SpawnBullet({ 0, 0 }, EDIRECTION::EAST);
	CBullet* pBullet2 = gameEngine.SpawnBullet({ 1, 0 }, EDIRECTION::WEST);

	// Bullets colliding at an angle
	CBullet* pBullet3 = gameEngine.SpawnBullet({ 2, 0 }, EDIRECTION::EAST);
	CBullet* pBullet4 = gameEngine.SpawnBullet({ 3, 1 }, EDIRECTION::NORTH);

	// Directly colliding bullets one space apart
	CBullet* pBullet5 = gameEngine.SpawnBullet({ 4, 0 }, EDIRECTION::EAST);
	CBullet* pBullet6 = gameEngine.SpawnBullet({ 6, 0 }, EDIRECTION::WEST);

	// Swap current system to the moving bullets system
	CMovingBulletsState* pState = new CMovingBulletsState;
	gameEngine.ChangeState(pState);

	// Run one step
	gameEngine.Step();

	// Check first set of bullets collide and are destroyed
	auto it1 = std::find(rvecpBullets.begin(), rvecpBullets.end(), pBullet1);
	auto it2 = std::find(rvecpBullets.begin(), rvecpBullets.end(), pBullet2);
	REQUIRE(it1 == rvecpBullets.end());
	REQUIRE(it2 == rvecpBullets.end());
	REQUIRE(rBoard.GetTile(0, 0).GetBullet() == nullptr);
	REQUIRE(rBoard.GetTile(1, 0).GetBullet() == nullptr);

	// Check second set of bullets collide and are destroyed
	auto it3 = std::find(rvecpBullets.begin(), rvecpBullets.end(), pBullet3);
	auto it4 = std::find(rvecpBullets.begin(), rvecpBullets.end(), pBullet4);
	REQUIRE(it3 == rvecpBullets.end());
	REQUIRE(it4 == rvecpBullets.end());
	REQUIRE(rBoard.GetTile(2, 0).GetBullet() == nullptr);
	REQUIRE(rBoard.GetTile(3, 0).GetBullet() == nullptr);
	REQUIRE(rBoard.GetTile(3, 1).GetBullet() == nullptr);

	// Check third set of bullets collide and are destroyed
	auto it5 = std::find(rvecpBullets.begin(), rvecpBullets.end(), pBullet5);
	auto it6 = std::find(rvecpBullets.begin(), rvecpBullets.end(), pBullet6);
	REQUIRE(it5 == rvecpBullets.end());
	REQUIRE(it6 == rvecpBullets.end());
	REQUIRE(rBoard.GetTile(4, 0).GetBullet() == nullptr);
	REQUIRE(rBoard.GetTile(5, 0).GetBullet() == nullptr);
	REQUIRE(rBoard.GetTile(6, 0).GetBullet() == nullptr);
}

TEST_CASE("Test bullets hitting edge of screen")
{
	// Init game engine
	CGameEngine gameEngine;

	std::vector<CBullet*>& rvecpBullets = gameEngine.GetBulletList();
	CBoard& rBoard = gameEngine.GetBoard();

	// Add some bullets
	CBullet* pBullet1 = gameEngine.SpawnBullet({ 0, 0 }, EDIRECTION::WEST);
	CBullet* pBullet2 = gameEngine.SpawnBullet({ 1, 0 }, EDIRECTION::NORTH);
	CBullet* pBullet3 = gameEngine.SpawnBullet({ 0, 9 }, EDIRECTION::SOUTH);
	CBullet* pBullet4 = gameEngine.SpawnBullet({ 9, 0 }, EDIRECTION::EAST);

	// Swap current system to the moving bullets system
	CMovingBulletsState* pState = new CMovingBulletsState;
	gameEngine.ChangeState(pState);

	// Run one step
	gameEngine.Step();
	// Check bullet1 is destroyed
	auto it1 = std::find(rvecpBullets.begin(), rvecpBullets.end(), pBullet1);
	REQUIRE(it1 == rvecpBullets.end());
	REQUIRE(rBoard.GetTile(0, 0).GetBullet() == nullptr);

	// Check bullet2 is destroyed
	auto it2 = std::find(rvecpBullets.begin(), rvecpBullets.end(), pBullet2);
	REQUIRE(it2 == rvecpBullets.end());
	REQUIRE(rBoard.GetTile(1, 0).GetBullet() == nullptr);

	// Check bullet3 is destroyed
	auto it3 = std::find(rvecpBullets.begin(), rvecpBullets.end(), pBullet3);
	REQUIRE(it3 == rvecpBullets.end());
	REQUIRE(rBoard.GetTile(0, 9).GetBullet() == nullptr);

	// Check bullet4 is destroyed
	auto it4 = std::find(rvecpBullets.begin(), rvecpBullets.end(), pBullet4);
	REQUIRE(it4 == rvecpBullets.end());
	REQUIRE(rBoard.GetTile(9, 0).GetBullet() == nullptr);
}