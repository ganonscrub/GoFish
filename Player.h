#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Card.h"

class Player
{
public:
	Player( bool isAI = false );

	int get_numMatches() const;
	CARD_RANK get_rankAt( int index ) const;

	void printHand() const;
	void printHand( unsigned posX, unsigned posY ) const;
	void printHandWithSelection( unsigned posX, unsigned posY, unsigned selectedIndex ) const;

	void printHandNew( unsigned posX, unsigned posY ) const;
	void printHandNewWithSelection( unsigned posX, unsigned posY, unsigned selectedIndex ) const;

	void printMatchPile() const;
	void printMatchPile( unsigned posX, unsigned posY ) const;

	int numCards() const;

	bool playerHasCardOfRank( CARD_RANK rank ) const;
	int checkHandForMatches();

	void addCard( Card in );
	void addMatches( std::vector <Card> in );

	void sortHand();

	std::vector< Card > cardsOfRank( CARD_RANK targetRank );

	Card cardAt( unsigned index ) const;

	bool isAI() const;

private:
	std::vector< Card > hand;
	std::vector< std::vector<Card> > matchPile;

	bool handSorted() const;
	const bool AIPlayer;

	void setConNorm() const;
	void setConRed() const;
	void setConBlack() const;
	void setConBySuit( CARD_SUIT inSuit ) const;
};

#endif