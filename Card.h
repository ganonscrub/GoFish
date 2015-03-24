#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <vector>

const char UPPER_LEFT = (const char)218;
const char STACKED_UPPER_LEFT = (const char)195;
const char STACKED_UPPER_RIGHT = (const char)180;
const char UPPER_RIGHT = (const char)191;
const char HORIZONTAL = (const char)196;
const char VERTICAL = (const char)179;
const char BOTTOM_LEFT = (const char)192;
const char BOTTOM_RIGHT = (const char)217;

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

const int CARD_WIDTH = 12;
const int CARD_HEIGHT = 12;

class Card
{
public:
	Card();
	Card( CARD_RANK rank, CARD_SUIT suit );
	void display_card( int x, int y, bool stacked = false, bool face_up = true ) const;
	char rankToChar( CARD_RANK rank ) const;
	void display_card_efficient( int x, int y ) const;

	//accessor functions
	CARD_RANK get_rank() const;
	CARD_SUIT get_suit() const;
	char rank_char() const { return rankToChar( cardRank ); }

	//mutator functions
	//void set_rank( CARD_RANK newRank ); never called
	//void set_suit( CARD_SUIT newSuit ); never called

	//operators
	bool operator==( const Card& right ) const;
	bool operator<( const Card& right ) const; // only cares about rank
	friend std::ostream& operator<<( std::ostream& out, const Card& card );

private:
	void display_stamp(int x, int y) const;
	CARD_RANK cardRank;
	CARD_SUIT cardSuit;
};

#endif