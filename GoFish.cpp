#include <iostream>
#include <vector>
#include <ctime>

#include "Game.h"

int main( int argc, char* argv )
{	
	int numOfPlayers = 0;
	srand( (unsigned)time( NULL ) );
	std::cout << "Enter the number of players(1-5): ";
	std::cin >> numOfPlayers;
	system("cls");
	Game game( numOfPlayers );

	game.run();

	return 0;
}