#include <iostream>
#include <vector>
#include <ctime>

#include "Game.h"

int main( int argc, char* argv )
{
	srand( (unsigned)time( NULL ) );

	Game game( 5 );

	game.run();

	return 0;
}