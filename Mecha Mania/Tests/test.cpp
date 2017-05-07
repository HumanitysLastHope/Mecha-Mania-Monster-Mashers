#include <conio.h>

#include <GameEngine.h>

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