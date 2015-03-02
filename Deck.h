#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"

class Deck
{
public:
	Deck();
	unsigned deckSize();
	void printDeck();
	void shuffleDeck();
	Card removeCard();

private:
	std::vector< Card > cards;
};

#endif