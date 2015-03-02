#include "Deck.h"

Deck::Deck()
{
	for ( int i = 0; i < 4; i++ )
	{
		for ( int j = 0; j < 13; j++ )
		{
			cards.push_back( Card( static_cast<CARD_SUIT>( SUIT_HEARTS + i ), static_cast<CARD_RANK>( RANK_ACE + j ) ) );
		}
	}
}

unsigned Deck::deckSize()
{
	return cards.size();
}

void Deck::printDeck()
{
	for ( unsigned i = 0; i < cards.size(); i++ )
	{
		cards[i].printCard();
		std::cout << "\t";
	}
}

void Deck::shuffleDeck()
{
	for ( unsigned i = 0; i < 1000; i++ )
	{
		int randPlace1 = rand() % 52, randPlace2 = rand() % 52;
		Card temp = cards[ randPlace1 ];
		cards[ randPlace1 ] = cards[ randPlace2 ];
		cards[ randPlace2 ] = temp;
	}
}

Card Deck::removeCard()
{
	if (deckSize() > 0){
		Card temp = cards.back();
		cards.pop_back();
		return temp;
	}
	else
		std::cout << "No more cards in deck!\n";
}