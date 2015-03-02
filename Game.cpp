#include "Game.h"

Game::Game(unsigned numPlayers) : numPlayers(numPlayers), initialHandSize(7), guesser(0), cardsNotInPlay(0)
{
	if ( numPlayers > 5 )
	{
		std::cout << "Too many players, setting it to 5\n\n\n\n";
		numPlayers = 5;
	}

	deck.shuffleDeck();

	for ( unsigned i = 0; i < numPlayers; i++ )
	{
		Player newPlayer;
		for ( unsigned j = 0; j < initialHandSize; j++ )
		{
			newPlayer.addCard( deck.removeCard() );
		}
		players.push_back( newPlayer );
	}
}

void Game::printDeck()
{
	deck.printDeck();
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

void Game::run()
{

	while (true)
	{
		if (deck.deckSize() <= 0 && cardsNotInPlay >= 52)
		{
			winner();
			break;
		}
		refreshDisplay();
		if (deck.deckSize() <= 0 && cardsNotInPlay >=52)
			winner();
		std::cout << "Currently guessing: Player " << guesser + 1 << "\n\n";
		guess( guesser );
		if ( guesser == players.size() - 1 )
			guesser = 0;
		else
			guesser++;
	}
}

void Game::guess(unsigned playerGuessing)
{
	if (players[playerGuessing].numCards() == 0 && deck.deckSize() > 0)
	{
		for (unsigned i = 0; i < initialHandSize && deck.deckSize() > 0; i++)
			players[playerGuessing].addCard(deck.removeCard());
		refreshDisplay();
		std::cout << "Currently guessing: Player " << guesser + 1 << "\n\n";
	}
	else if (players[playerGuessing].numCards() == 0 && deck.deckSize() == 0)
	{
		std::cout << "Player " << playerGuessing + 1 << " skipped. No cards in deck or in hand\n";
		return;
	}
	else{
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
		std::vector< Card > temp = players[targetPlayer - 1].cardsOfRank(static_cast<CARD_RANK>(guessRank));
		if (temp.size() > 0) // if the player had card(s) of that rank
		{
			std::cout << "\nFound cards: ";
			temp[0].printCard();
			for (unsigned i = 1; i < temp.size(); i++)
			{
				std::cout << ", ";
				temp[i].printCard();
			}
			std::cout << "\n";
			for (unsigned i = 0; i < temp.size(); i++)
				players[playerGuessing].addCard(temp[i]);
			guesser--;
		}
		else
		{
			if (deck.deckSize() > 0)
			{
				std::cout << "\nDid not find any cards. Take one from the pile\n";
				Card tempCard = deck.removeCard();
				std::cout << "Card drawn: ";
				tempCard.printCard();
				std::cout << std::endl;
				if (tempCard.getRank() == static_cast<CARD_RANK> (guessRank))
					guesser--;
				players[playerGuessing].addCard(tempCard);
			}
			else
				std::cout << "\nNo more cards to draw, continuing...\n";
		}
		for (unsigned i = 0; i < players[playerGuessing].numCards(); i++)
			if (selfCheckHandForMatches(players[playerGuessing].get_rankAt(i), playerGuessing))
				i = -1;
	}
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
bool Game::selfCheckHandForMatches(int guessRank, unsigned player)
{
	std::vector< Card> temp = players[player].cardsOfRank(static_cast<CARD_RANK> (guessRank));
	if (temp.size() == 4)
	{
		players[player].addMatches(temp);
		temp.clear();
		cardsNotInPlay += 4;
		return true;
	}
	else
	{
		for (unsigned i = 0; i < temp.size(); i++)
			players[player].addCard(temp[i]);
		return false;
	}
}
void Game::refreshDisplay()
{
	std::cout << "\n--------------------------------------------------------------------------------\n";
	for (unsigned i = 0; i < players.size(); i++)
	{
		std::cout << "Player " << i + 1 << " hand: \t\t";
		players[i].printHand();
		std::cout << std::endl;
		std::cout << "Player " << i + 1 << " match pile: ";
		players[i].printMatchPile();
		std::cout << std::endl;
	}
	std::cout << "Cards in Deck: " << deck.deckSize() << std::endl;
	std::cout << "--------------------------------------------------------------------------------\n";
}