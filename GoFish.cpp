#include <iostream>
#include <vector>
#include <ctime>

#include "Game.h"

int main( int argc, char* argv )
{
	srand( (unsigned)time( NULL ) );

	system( "mode 120, 42" );

	int numOfPlayers = 0;
	char aiGame = 'n';

	gotoxy( 5, 3 );
	std::cout << "Enter the number of players( 2-5 ): ";
	std::cin >> numOfPlayers;

	gotoxy( 5, 4 );
	std::cout << "Would you like to play against computer players? (y/n): ";
	std::cin >> aiGame;

	system( "cls" );

	if ( aiGame == 'y' )
	{
		Game game( numOfPlayers, true );
		game.run();
	}
	else
	{
		Game game( numOfPlayers, false );
		game.run();
	}

	return 0;
}