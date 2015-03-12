#include "Game.h"
#include <conio.h>

Game::Game(unsigned numOfRealPlayers, unsigned numOfAIPlayers, unsigned numPlayers, bool isAIGame) 
	: numOfRealPlayers(numOfRealPlayers), numOfAIPlayers(numOfAIPlayers), numPlayers(numPlayers), isAIGame(isAIGame), initialHandSize(7), guesser(0), cardsNotInPlay(0)
{
	if ( numPlayers < 2)
	{
		std::cout << "Too few players, setting it to 2\n\n\n\n";
		Game::numOfRealPlayers = 2;
		Game::numOfAIPlayers = 0;
	}
	else if ( numPlayers > 5)
	{
		std::cout << "Too many players, setting it to 5\n\n\n\n";
		Game::numOfRealPlayers = 5;
		Game::numOfAIPlayers = 0;
	}
	Game::numPlayers = Game::numOfAIPlayers + Game::numOfRealPlayers;

	deck.shuffleDeck();
	for (unsigned i = 0; i < numPlayers;)
	{
		unsigned j = 0; unsigned k = 0;
		if (j < numOfRealPlayers)
		{
			players.push_back( Player() );
			j++;
			i++;
		}
		if (k < numOfAIPlayers)
		{
			players.push_back( Player(true) );
			k++;
			i++;
		}

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
	while ( targetPlayer < 1 || targetPlayer > numPlayers || targetPlayer - 1 == playerGuessing )
	{
		gotoxy( targetPlayerX, targetPlayerY );
		std::cout << "Target player: ";
		std::cin >> targetPlayer;
		std::cin.clear();
		std::cin.ignore( 1000, '\n' );
	}

	
		gotoxy( guessRankX, guessRankY );

		std::cout << "Select a card by using the arrow keys ";

		int c = 0; int indexOfCardSelected = 0;
		gotoxy(guessRankX, guessRankY + 1);
		std::cout << "Index of selected card: " << indexOfCardSelected;
		while ((c = _getch()) != KEY_ENTER)
		{
			if (c == 0 || c == 224)
				c = _getch();
			switch (c)
			{
			case KEY_LEFT:
				indexOfCardSelected--;
				if (indexOfCardSelected < 0)
					indexOfCardSelected = players[playerGuessing].numCards() - 1;
				break;
			case KEY_RIGHT:
				indexOfCardSelected++;
				if (indexOfCardSelected >= players[playerGuessing].numCards())
					indexOfCardSelected = 0;
				break;
			default:
				break;
			}
			gotoxy(guessRankX, guessRankY + 1);
			std::cout << "Index of selected card: " << indexOfCardSelected;
			c = 0;
		}

	CARD_RANK guessedRank = static_cast<CARD_RANK>(players[playerGuessing].get_rankAt(indexOfCardSelected));
	checkForMatches(guesser, targetPlayer, guessedRank, playerGuessing);

	
}

void Game::computerGuess( unsigned playerNumber )
{
	unsigned randPlayer = -1;
	while (randPlayer < 1 || randPlayer > numPlayers || randPlayer == playerNumber)
		randPlayer = rand() % numPlayers + 1;


	Card randCard = players[playerNumber].cardAt( rand() % players[playerNumber].numCards() );
	CARD_RANK randRank = randCard.get_rank();

	checkForMatches(guesser, randPlayer, randRank, playerNumber);
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
void Game::checkForMatches(unsigned guesser, unsigned targetPlayer, CARD_RANK guessedRank, unsigned playerGuessing)
{
	std::vector< Card > temp = players[targetPlayer - 1].cardsOfRank(guessedRank);
	if (temp.size() > 0) // if the target player has a card/cards of that rank
	{
		players[targetPlayer - 1].sortHand(); // sort hand of player who just lost cards

		gotoxy(acquiredCardX, acquiredCardY - 1);
		std::cout << "Acquired card(s)!";
		for (unsigned i = 0; i < temp.size(); i++)
			temp[i].display_card(acquiredCardX + i + (i * 2), acquiredCardY);

		std::cout << "\n";
		for (unsigned i = 0; i < temp.size(); i++)
			players[playerGuessing].addCard(temp[i]);

		guesser--;

		gotoxy(0, 35);
	}
	else
	{
		gotoxy(acquiredCardX - 10, acquiredCardY - 2);
		std::cout << "Player " << targetPlayer << " had no cards of that rank.";

		if (deck.deckSize() > 0)
		{
			gotoxy(acquiredCardX - 5, acquiredCardY - 1);
			std::cout << "Take one from the pile:";
			Card tempCard = deck.removeCard();

			if (tempCard.get_rank() == guessedRank)
				guesser--;

			players[playerGuessing].addCard(tempCard);
			tempCard.display_card(acquiredCardX, acquiredCardY);
		}
		else
		{
			gotoxy(acquiredCardX - 10, acquiredCardY - 1);
			std::cout << "No more cards to draw, continuing...";
		}
	}

	cardsNotInPlay += (players[playerGuessing].checkHandForMatches() * 4); //finds matches and increments cardsNotInPlay
	players[playerGuessing].sortHand();
}