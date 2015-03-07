#ifndef CARD_H
#define CARD_H

#include <iostream>

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

enum CARD_SUIT 
{ 
	SUIT_HEARTS = 3, 
	SUIT_DIAMONDS, 
	SUIT_CLUBS, 
	SUIT_SPADES 
};

void gotoxy(int x, int y);

const int WIDTH = 12;
const int HEIGHT = 12;

class Card
{
public:
	Card();
	Card( CARD_RANK rank, CARD_SUIT suit );
	void display_card( int x, int y, bool stacked = false, bool face_up = true ) const;

	//accessor functions
	CARD_RANK get_rank() const;
	CARD_SUIT get_suit() const;

	//mutator functions
	void set_rank( CARD_RANK newRank );
	void set_suit( CARD_SUIT newSuit );

	//operators
	bool operator==( const Card& right ) const;
	bool operator<( const Card& right ) const; // only cares about rank
	friend std::ostream& operator<<( std::ostream& out, const Card& card );

private:
	void display_stamp(int x, int y) const;
	CARD_RANK rank;
	CARD_SUIT suit;
};

#endif