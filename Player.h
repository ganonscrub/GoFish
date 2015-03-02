#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Card.h"

class Player
{
public:
	Player();

	int get_numMatches() const;
	int get_rankAt( int index ) const;

	void printHand();
	void printMatchPile() const;
	unsigned numCards() const;

	bool playerHasCard( Card test );

	void addCard( Card in );
	void addMatches( std::vector <Card> in );

	std::vector< Card > cardsOfRank( CARD_RANK targetRank );

private:
	std::vector< Card > hand;
	std::vector< std::vector<Card> > matchPile;
};

#endif