#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Card.h"

class Player
{
public:
	Player();
	void addCard( Card in );
	void addMatches(std::vector <Card> in);
	void printHand();
	void printMatchPile();
	bool playerHasCard( Card test );
	std::vector< Card > cardsOfRank( CARD_RANK targetRank );
	unsigned numCards();
	int get_numMatches();
	int get_rankAt(int index);
private:
	std::vector< Card > hand;
	std::vector<std::vector<Card> >matchPile;
	int matches;
};

#endif