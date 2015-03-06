 #include "Game.h"

Game::Game( unsigned numPlayers ) : numPlayers( numPlayers ), initialHandSize( 7 ), guesser( 0 ), cardsNotInPlay( 0 )
{
	if ( numPlayers < 2 )
	{
		std::cout << "Too few players, setting it to 2\n\n\n\n";
		numPlayers = 2;
	}
	else if ( numPlayers > 5 )
	{
		std::cout << "Too many players, setting it to 5\n\n\n\n";
		numPlayers = 5;
	}

	deck.shuffleDeck();

	for ( unsigned i = 0; i < numPlayers; i++ )
		players.push_back( Player() );

	dealCards();
}
void Game::dealCards()
{
	for (unsigned i = 0; i < numPlayers; i++)
	{
		for (unsigned j = 0; j < initialHandSize; j++)
			players[ i ].addCard( deck.removeCard() );
		players[ i ].sortHand(); // sort after adding the cards, should be a better way to optimize
	}
}

void Game::run()
{
	while ( cardsNotInPlay < 52 )
	{
		gotoxy( playerLabelX, playerLabelY );
		std::cout << "Currently guessing: Player " << guesser + 1;
		if ( players[ guesser ].numCards() == 0 )
		{
			for ( unsigned i = 0; i < initialHandSize && deck.deckSize() > 0; i++ )
			{
				players[ guesser ].addCard( deck.removeCard() );
				players[ guesser ].sortHand();
			}
		}
		printPlayerHand( guesser );

		gotoxy( playerMatchX, playerMatchY - 1 );
		std::cout << "Player " << guesser + 1 << " matched cards:";
		printPlayerMatchPile( guesser );

		guess( guesser );
		if ( guesser == players.size() - 1 )
			guesser = 0;
		else
			guesser++;

		gotoxy( 0, guessRankY + 2 );

		system( "pause" );
		system( "cls" );
	}

	winner();
}

void Game::printPlayerHands()
{
	for ( unsigned i = 0; i < numPlayers; i++ )
	{
		std::cout << "Player " << i + 1 << ": ";
		players[i].printHand();
		std::cout << "\n";
	}
}

void Game::printPlayerMatchPile( unsigned playerNumber ) const
{
	players[ playerNumber ].printMatchPile( playerMatchX, playerMatchY );
}

void Game::printPlayerHand( unsigned playerNumber ) const
{
	players[ playerNumber ].printHand( playerHandX, playerHandY );
}

void Game::guess( unsigned playerGuessing )
{
	unsigned targetPlayer = -1;
	char guessRank = 0;
	while ( targetPlayer < 1 || targetPlayer > numPlayers || targetPlayer - 1 == playerGuessing )
	{
		gotoxy( targetPlayerX, targetPlayerY );
		std::cout << "Target player: ";
		std::cin >> targetPlayer;
		std::cin.clear();
		std::cin.ignore( 1000, '\n' );
	}

	while ( guessRank < RANK_ACE || guessRank > RANK_KING )
	{
		gotoxy( guessRankX, guessRankY );
		std::cout << "Guess rank: ";
		std::cin >> guessRank;
		std::cin.clear();
		std::cin.ignore( 1000, '\n' );
		switch ( guessRank )
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

	std::vector< Card > temp = players[ targetPlayer - 1 ].cardsOfRank( static_cast<CARD_RANK>( guessRank ) );
	if ( temp.size() > 0 ) // if the target player has a card/cards of that rank
	{
		players[ targetPlayer - 1 ].sortHand(); // sort hand of player who just lost cards

		gotoxy( acquiredCardX, acquiredCardY - 1 );
		std::cout << "Acquired card(s)!";
		for ( unsigned i = 0; i < temp.size(); i++ )
			temp[i].display_card( acquiredCardX + i + ( i * 2 ), acquiredCardY );

		std::cout << "\n";
		for ( unsigned i = 0; i < temp.size(); i++ )
			players[ playerGuessing ].addCard( temp[ i ] );
		players[ playerGuessing ].sortHand();

		guesser--;

		gotoxy( 0, 35 );
	}
	else
	{
		if ( deck.deckSize() > 0 )
		{
			gotoxy( acquiredCardX - 10, acquiredCardY - 2 );
			std::cout << "Player " << targetPlayer << " had no cards of that rank.";
			gotoxy( acquiredCardX - 5, acquiredCardY - 1 );
			std::cout << "Take one from the pile:";
			Card tempCard = deck.removeCard();

			if ( tempCard.get_rank() == static_cast<CARD_RANK> (guessRank) )
				guesser--;

			players[ playerGuessing ].addCard( tempCard );
			players[ playerGuessing ].sortHand();
			tempCard.display_card( acquiredCardX, acquiredCardY );
		}
		else
		{
			gotoxy( acquiredCardX, acquiredCardY - 1 );
			std::cout << "No more cards to draw, continuing...";
		}
	}

	cardsNotInPlay += ( players[ playerGuessing ].checkHandForMatches() * 4 ); //finds matches and increments cardsNotInPlay
}

void Game::winner()
{
	std::vector<int> winner;
	int max = 0;
	for ( unsigned i = 0; i < numPlayers; i++ )
	{
		if ( players[ i ].get_numMatches() > max )
		{
			winner.clear();
			max = players[ i ].get_numMatches();
			winner.push_back( i + 1 );
		}
		else if ( players[i].get_numMatches() == max )
			winner.push_back( i + 1 );
	}
	std::cout << "Winner(s): ";
	for ( unsigned i = 0; i < winner.size(); i++ )
	{
		std::cout << winner.back() << ", ";
		winner.pop_back();
	}
	std::cout << std::endl;
}