 #include "Game.h"

Game::Game(unsigned numPlayers) : numPlayers(numPlayers), initialHandSize(7), guesser(0), cardsNotInPlay(0)
{
	if (numPlayers < 2)
	{
		std::cout << "Too few players, setting it to 2\n\n\n\n";
		numPlayers = 2;
	}
	else if ( numPlayers > 5)
	{
		std::cout << "Too many players, setting it to 5\n\n\n\n";
		numPlayers = 5;
	}

	deck.shuffleDeck();

	for ( unsigned i = 0; i < numPlayers; i++ )
	{
		Player newPlayer;
		players.push_back( newPlayer );
	}
	dealCards();
}
void Game::dealCards()
{
	for (unsigned i = 0; i < initialHandSize; i++)
	{
		for (unsigned j = 0; j < numPlayers; j++)
			players[j].addCard(deck.removeCard());
	}
}

/*void Game::printPlayerHands()
{
	for ( unsigned i = 0; i < numPlayers; i++ )
	{
		std::cout << "Player " << i + 1 << ": ";
		players[i].printHand();
		std::cout << "\n";
	}
} Used to print all player hands for testing*/

void Game::run()
{

	system( "mode 90, 40" );

	while (cardsNotInPlay < 52)
	{
		gotoxy( 8, 2 );
		std::cout << "Player " << guesser + 1;
		printPlayerHand( guesser );
		gotoxy( 0, 21 );
		gotoxy( 8, 2 );
		std::cout << "Player " << guesser + 1;
		if (players[guesser].numCards() == 0){
			for ( unsigned i = 0; i < initialHandSize && deck.deckSize() > 0; i++ )
				players[ guesser ].addCard( deck.removeCard() );
		}
		printPlayerHand( guesser );
		gotoxy(8, 17);
		std::cout << "Matches";
		printPlayerMatchPile( guesser );
		gotoxy(0, 30);
		guess( guesser );
		if ( guesser == players.size() - 1 )
			guesser = 0;
		else
			guesser++;

		system( "pause" );
		system( "cls" );
	}
	winner();
}

void Game::guess( unsigned playerGuessing )
{
	unsigned targetPlayer = -1;
	char guessRank = 0;
	while (targetPlayer < 1 || targetPlayer > numPlayers || targetPlayer - 1 == playerGuessing)
	{
		std::cout << "Target player: ";
		std::cin >> targetPlayer;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	while (guessRank < RANK_ACE || guessRank > RANK_KING)
	{
		std::cout << "Guess rank: ";
		std::cin >> guessRank;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		switch (guessRank)
		{
		case RANK_ACE:
		case '1':
		case 'a':
		case 'A':
			guessRank = static_cast<int>(RANK_ACE);
			break;
		case RANK_TEN:
		case 't':
		case 'T':
			guessRank = static_cast<int>(RANK_TEN);
			break;
		case RANK_JACK:
		case 'j':
		case 'J':
			guessRank = static_cast<int>(RANK_JACK);
			break;
		case RANK_QUEEN:
		case 'q':
		case 'Q':
			guessRank = static_cast<int>(RANK_QUEEN);
			break;
		case RANK_KING:
		case 'k':
		case 'K':
			guessRank = static_cast<int>(RANK_KING);
			break;
		default:
			guessRank -= '0';
		}
	}

	std::vector< Card > temp = players[ targetPlayer - 1 ].cardsOfRank(static_cast<CARD_RANK>( guessRank ) );
	if (temp.size() > 0) // if the player had card(s) of that rank
	{
		gotoxy( 70, 9 );
		std::cout << "Acquired card(s)!";
		for (unsigned i = 0; i < temp.size(); i++)
			temp[i].display_card( 70 + i + ( i * 2 ), 10 );

		std::cout << "\n";
		for (unsigned i = 0; i < temp.size(); i++)
			players[ playerGuessing ].addCard( temp[ i ] );
		guesser--;

		gotoxy( 0, 35 );

	}
	else
	{
		if ( deck.deckSize() > 0 )
		{
			gotoxy( 0, 34 );
			std::cout << "\nDid not find any cards. Take one from the pile\n";
			Card tempCard = deck.removeCard();
			tempCard.display_card( 70, 10 );
			gotoxy( 0, 35 );

			std::cout << std::endl;
			if (tempCard.get_rank() == static_cast<CARD_RANK> (guessRank))
				guesser--;
			players[playerGuessing].addCard(tempCard);
		}
		else
			std::cout << "\nNo more cards to draw, continuing...\n";
	}
	cardsNotInPlay += (players[playerGuessing].checkHandForMatches() * 4); //finds matches and increments cardsNotInPlay

}
void Game::winner()
{
	std::vector<int> winner;
	int max = 0;
	for (unsigned i = 0; i < numPlayers; i++)
	{
		if (players[i].get_numMatches() > max)
		{
			winner.clear();
			max = players[i].get_numMatches();
			winner.push_back(i + 1);
		}
		else if (players[i].get_numMatches() == max)
			winner.push_back(i+1);
	}
	std::cout << "Winner(s): ";
	for (unsigned i = 0; i < winner.size(); i++)
	{
		std::cout << winner.back() << ", ";
		winner.pop_back();
	}
	std::cout << std::endl;
}

void Game::printPlayerHand( unsigned playerNumber )
{
	players[ playerNumber ].printHand();

}

void Game::printPlayerMatchPile(unsigned playerNumber)
{
	players[playerNumber].printMatchPile();
}