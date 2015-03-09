#include <iostream>
#include <vector>
#include <ctime>

#include "Game.h"

int main(int argc, char* argv)
{
	srand((unsigned)time(NULL));

	system("mode 120, 42");

	int numOfPlayers = 0;
	int  T = 0;

	//Would crash if a number larger then 10 was entered or a letter so I reworked it a bit.
	while (T != 1){
		std::cout << "Enter the number of players( 2-5 ): ";
		std::cin >> numOfPlayers;
		if ((2 <= numOfPlayers) && (numOfPlayers <= 5)){
			T = 1;
		}
		//elsif(numOfPlayers >)
		else{
			std::cout << "Invalid number of players\n\n\n";
			std::cin.clear();
			std::cin.ignore();
		}
	}

	system("cls");

	Game game(numOfPlayers);

	game.run();

	return 0;
}
