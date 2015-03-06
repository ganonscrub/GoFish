#include <iostream>
#include <vector>
#include <ctime>

#include "Game.h"

int main( int argc, char* argv )
{
	srand( (unsigned)time( NULL ) );

	system( "mode 120, 42" );

	int numOfPlayers = 0;

	std::cout << "Enter the number of players( 2-5 ): ";
	std::cin >> numOfPlayers;

	system("cls");

	Game game( numOfPlayers );

	game.run();

	return 0;
}