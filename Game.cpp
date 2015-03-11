 #include "Game.h"

Game::Game( unsigned numPlayers, bool hasAI ) : numPlayers( numPlayers ), hasAI( hasAI ), initialHandSize( 7 ), guesser( 0 ), cardsNotInPlay( 0 )
{
	if ( numPlayers < 2 )
	{
		std::cout << "Too few players, setting it to 2\n\n\n\n";
		Game::numPlayers = 2;
	}
	else if ( numPlayers > 5 )
	{
		std::cout << "Too many players, setting it to 5\n\n\n\n";
		Game::numPlayers = 5;
	}

	deck.shuffleDeck();

	if ( hasAI )
	{
		for ( unsigned i = 0; i < numPlayers; i++ )
		{
			if ( i == 0 )
				players.push_back( Player() );
			else
				players.push_back( Player( true ) );
		}
	}
	else
	{
		for ( unsigned i = 0; i < numPlayers; i++ )
			players.push_back( Player() );
	}

	dealCards();
}
void Game::dealCards()
{
	for (unsigned i = 0; i < numPlayers; i++)
	{
		for (unsigned j = 0; j < initialHandSize; j++)
			players[i].addCard( deck.removeCard() );
		players[i].sortHand(); // sort after adding the cards, should be a better way to optimize
	}
}

std::vector< Player >& Game::getPlayers()
{
	return players;
}

void Game::run()
{
	while ( cardsNotInPlay < 52 )
	{
		// skip player if no more cards in hand & no cards in deck
		while ( players[guesser].numCards() == 0 && deck.deckSize() <= 0 && cardsNotInPlay < 52 )
		{
			gotoxy( playerLabelX, playerLabelY );
			std::cout << "Skipping Player " << guesser + 1 << " due to an empty hand and an empty deck";

			if ( guesser == players.size() - 1 )
				guesser = 0;
			else
				guesser++;

			gotoxy( guessRankX, guessRankY + 1 );
			system( "pause" );
		}

		gotoxy( playerLabelX, playerLabelY );
		std::cout << "                                                                      ";
		gotoxy( playerLabelX, playerLabelY );
		std::cout << "Currently guessing: Player " << guesser + 1 << " out of " << numPlayers << " players";
		gotoxy( cardsLeftInPlayX, cardsLeftInPlayY );
		std::cout << "Cards in play: " << 52 - cardsNotInPlay;

		if ( !players[guesser].isAI() )
		{
			gotoxy( playerLabelX, playerLabelY + 2 );
			std::cout << "Player " << guesser + 1 << " Hand";
		}

		// if current guesser has no cards, give guesser a card from the deck
		if ( players[guesser].numCards() == 0 )
		{
			for ( unsigned i = 0; i < initialHandSize && deck.deckSize() > 0; i++ )
			{
				players[guesser].addCard( deck.removeCard() );
			}
			players[guesser].sortHand();
		}

		if ( !players[guesser].isAI() )
			printPlayerHand( guesser );

		gotoxy( playerMatchX, playerMatchY - 1 );
		std::cout << "Player " << guesser + 1 << " matched cards:";
		printPlayerMatchPile( guesser );

		if ( players[guesser].isAI() )
			computerGuess( guesser );
		else
			guess( guesser );

		if ( guesser == players.size() - 1 )
			guesser = 0;
		else
			guesser++;

		gotoxy( guessRankX, guessRankY + 1 );
		std::cout << "                                                                           ";
		gotoxy( guessRankX, guessRankY + 1 );

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
	players[playerNumber].printMatchPile( playerMatchX, playerMatchY );
}

void Game::printPlayerHand( unsigned playerNumber ) const
{
	players[playerNumber].printHand( playerHandX, playerHandY );
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
		gotoxy( guessRankX + 12, guessRankY );
		std::cout << "   ";
		gotoxy( guessRankX + 12, guessRankY );

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
			if ( guessRank >= '1' && guessRank <= '9' )
				guessRank -= '0';
		}

		if ( !players[playerGuessing].playerHasCardOfRank( static_cast<CARD_RANK>(guessRank) ) )
		{
			gotoxy( guessRankX, guessRankY + 1 );
			std::cout << "No card of that rank in your hand, cheater!\n";
			guessRank = 0;
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
			players[playerGuessing].addCard( temp[ i ] );

		guesser--;

		gotoxy( 0, 35 );
	}
	else
	{
		gotoxy( acquiredCardX - 10, acquiredCardY - 2 );
		std::cout << "Player " << targetPlayer << " had no cards of that rank.";

		if ( deck.deckSize() > 0 )
		{
			gotoxy( acquiredCardX - 5, acquiredCardY - 1 );
			std::cout << "Take one from the pile:";
			Card tempCard = deck.removeCard();

			if ( tempCard.get_rank() == static_cast<CARD_RANK> (guessRank) )
				guesser--;

			players[playerGuessing].addCard( tempCard );
			tempCard.display_card( acquiredCardX, acquiredCardY );
		}
		else
		{
			gotoxy( acquiredCardX - 10, acquiredCardY - 1 );
			std::cout << "No more cards to draw, continuing...";
		}
	}

	cardsNotInPlay += ( players[playerGuessing].checkHandForMatches() * 4 ); //finds matches and increments cardsNotInPlay
	players[playerGuessing].sortHand();
}

void Game::computerGuess( unsigned playerNumber )
{
	unsigned randPlayer = -1;
	while ( randPlayer < 0 || randPlayer > numPlayers - 1 || randPlayer == playerNumber )
		randPlayer = rand() % numPlayers;

	Card randCard = players[playerNumber].cardAt( rand() % players[playerNumber].numCards() );
	CARD_RANK randRank = randCard.get_rank();

	std::vector< Card > temp = players[randPlayer].cardsOfRank( randRank );
	if ( temp.size() > 0 )
	{
		players[randPlayer].sortHand(); // sort hand of player who just lost cards

		gotoxy( acquiredCardX, acquiredCardY - 1 );
		std::cout << "Acquired card(s)!";
		for ( unsigned i = 0; i < temp.size(); i++ )
			temp[i].display_card( acquiredCardX + i + ( i * 2 ), acquiredCardY );

		std::cout << "\n";
		for ( unsigned i = 0; i < temp.size(); i++ )
			players[playerNumber].addCard( temp[ i ] );

		guesser--;

		gotoxy( 0, 35 );
	}
	else
	{
		gotoxy( acquiredCardX - 10, acquiredCardY - 2 );
		std::cout << "Player " << randPlayer + 1 << " had no cards of that rank.";

		if ( deck.deckSize() > 0 )
		{
			gotoxy( acquiredCardX - 5, acquiredCardY - 1 );
			std::cout << "Took from the pile";
			Card tempCard = deck.removeCard();

			if ( tempCard.get_rank() == static_cast<CARD_RANK> (randRank) )
				guesser--;

			players[playerNumber].addCard( tempCard );
		}
		else
		{
			gotoxy( acquiredCardX - 10, acquiredCardY - 1 );
			std::cout << "No more cards to draw, continuing...";
		}
	}

	cardsNotInPlay += ( players[playerNumber].checkHandForMatches() * 4 ); //finds matches and increments cardsNotInPlay
	players[playerNumber].sortHand();
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

	gotoxy( winnersX, winnersY );
	std::cout << "Winner(s): ";
	std::cout << "Player " << winner[0];
	for ( unsigned i = 1; i < winner.size(); i++ )
		std::cout << ", Player " << winner[i];
	std::cout << std::endl;
	gotoxy( winnersX - 6, winnersY + 1 );
}