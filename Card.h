#ifndef CARD_H
#define CARD_H

#include <iostream>

enum CARD_SUIT
{
	SUIT_HEARTS = 3,
	SUIT_DIAMONDS,
	SUIT_CLUBS,
	SUIT_SPADES
};

enum CARD_RANK
{
	RANK_ACE = 1,
	RANK_TWO,
	RANK_THREE,
	RANK_FOUR,
	RANK_FIVE,
	RANK_SIX,
	RANK_SEVEN,
	RANK_EIGHT,
	RANK_NINE,
	RANK_TEN,
	RANK_JACK,
	RANK_QUEEN,
	RANK_KING
};

class Card
{
public:
	Card();
	Card( CARD_SUIT suit, CARD_RANK rank );

	void printCard();

	void setSuit( CARD_SUIT newSuit ) { suit = newSuit; }
	void setRank( CARD_RANK newRank ) { rank = newRank; }

	CARD_SUIT getSuit() const { return suit; }
	CARD_RANK getRank() const { return rank; }

	bool operator==( const Card& right );

private:
	CARD_SUIT suit;
	CARD_RANK rank;
};

#endif