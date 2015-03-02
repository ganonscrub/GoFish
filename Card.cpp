#include "Card.h"

Card::Card()
{
	suit = SUIT_HEARTS;
	rank = RANK_ACE;
}

Card::Card( CARD_SUIT suit, CARD_RANK rank ) : suit( suit ), rank( rank )
{
}

void Card::printCard()
{
	switch ( rank )
	{
	case RANK_ACE:
		std::cout << 'A';
		break;
	case RANK_TEN:
		std::cout << 'T';
		break;
	case RANK_JACK:
		std::cout << 'J';
		break;
	case RANK_QUEEN:
		std::cout << 'Q';
		break;
	case RANK_KING:
		std::cout << 'K';
		break;
	default:
		std::cout << int(rank);
	}

	std::cout << (char)suit;
}

bool Card::operator==( const Card& right )
{
	return ( rank == right.rank && suit == right.suit );
}