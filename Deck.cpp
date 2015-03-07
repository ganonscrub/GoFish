#include "Deck.h"

Deck::Deck()
{
	for ( int i = 0; i < 13; i++ )
	{
		for ( int j = 0; j < 4; j++ )
		{
			cards.push_back( Card( static_cast<CARD_RANK>( RANK_ACE + i ), static_cast<CARD_SUIT>( SUIT_HEARTS + j ) ) );
		}
	}
}

unsigned Deck::deckSize()
{
	return cards.size();
}
void Deck::shuffleDeck()
{
	for ( unsigned i = 0; i < 1000; i++ )
	{
		int randPlace1 = rand() % 52, randPlace2 = rand() % 52;
		Card temp = cards[randPlace1];
		cards[randPlace1] = cards[randPlace2];
		cards[randPlace2] = temp;
	}
}

Card Deck::removeCard()
{
	if ( deckSize() > 0 )
	{
		Card temp = cards.back();
		cards.pop_back();
		return temp;
	}
	else
	{
		std::cout << "No more cards in deck\n";
		return Card( static_cast<CARD_RANK>( -1 ), static_cast<CARD_SUIT>( -1 ) );
	}
}