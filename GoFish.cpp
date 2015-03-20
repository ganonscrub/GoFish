#include <iostream>
#include <vector>
#include <ctime>

#include "Game.h"

int main( int argc, char* argv )
{
	srand( (unsigned)time( NULL ) );

	system( "mode 120, 42" );

	int numOfPlayers = 0;
	int numOfAIPlayers = 0;
	char yesNoResponse = 'n';
	bool isAIGame = false;

	gotoxy( 5, 3 );
	std::cout << "Enter the number of players( 2-5 ): ";
	std::cin >> numOfPlayers;

	gotoxy( 5, 4 );
	std::cout << "Would you like to play against computer players? (y/n): ";
	std::cin >> yesNoResponse;
	if (yesNoResponse == 'y')
	{
		isAIGame = true;
		gotoxy(5, 5);
		std::cout << "How many of the players are AI players? (0-" << numOfPlayers << ")? ";
		std::cin >> numOfAIPlayers;
	}

	system( "cls" );
	Game game(numOfPlayers - numOfAIPlayers,numOfAIPlayers, numOfPlayers, isAIGame);
	game.run();

	return 0;
}