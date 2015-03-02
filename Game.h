#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "Player.h"
#include "Deck.h"

class Game
{
public:
	Game( unsigned numPlayers );
	void dealCards();
	std::vector< Player > *getPlayers() { return &players; }
	void printDeck();
	void printPlayerHands();
	void run();
	void guess( unsigned playerGuessing );
	void winner();
	bool selfCheckHandForMatches(int guessRank, unsigned player);
	void refreshDisplay();

private:
	Deck deck;
	const unsigned numPlayers;
	const unsigned initialHandSize;
	int cardsNotInPlay;
	std::vector< Player > players;
	unsigned guesser;
};

#endif