#include "Player.h"

Player::Player()
{
}

int Player::get_numMatches() const
{
	return matchPile.size();
}
int Player::get_rankAt(int index) const
{
	return hand[index].get_rank();
}

void Player::printHand() const
{
	for ( unsigned i = 0; i < hand.size(); i++ )
		hand[i].display_card( i * WIDTH + 8 - ( i * 9 ), 3 );
}

void Player::printHand( unsigned posX, unsigned posY ) const
{
	for ( unsigned i = 0; i < hand.size(); i++ )
		hand[i].display_card( i * WIDTH + posX - ( i * 9 ), posY );
}

void Player::printMatchPile() const
{
	for ( unsigned i = 0; i < matchPile.size(); i++ )
		matchPile[i][0].display_card( i * WIDTH + 8 - ( i * 10 ), 18 );
}

void Player::printMatchPile( unsigned posX, unsigned posY ) const
{
	for ( unsigned i = 0; i < matchPile.size(); i++ )
		matchPile[i][0].display_card( i * WIDTH + posX - ( i * 10 ), posY );
}

unsigned Player::numCards() const
{
	return hand.size();
}

bool Player::playerHasCardOfRank( CARD_RANK rank ) const
{
	for ( unsigned i = 0; i < hand.size(); i++ )
	{
		if ( hand[i].get_rank() == rank )
			return true;
	}
	return false;
}

void Player::addCard( Card in )
{
	hand.push_back( in );
}

void Player::addMatches( std::vector<Card> in )
{
	matchPile.push_back( in );
}

std::vector< Card > Player::cardsOfRank( CARD_RANK targetRank )
{
	std::vector< Card > temp;
	for ( unsigned i = 0; i < hand.size(); i++ )
	{
		if ( hand[i].get_rank() == targetRank )
		{
			temp.push_back( hand[i] );
			hand.erase( hand.begin() + i );
			i = -1;
		}
	}
	return temp;
}

int Player::checkHandForMatches()
{	
	int initialNumberOfMatches = matchPile.size();
	for ( unsigned i = 0; i < numCards(); i++ )
	{
		std::vector< Card > temp = cardsOfRank( static_cast<CARD_RANK>( get_rankAt( i ) ) );
		if ( temp.size() == 4 )
		{
			addMatches( temp );
			temp.clear();
			i = -1;			
		}
		else
		{
			for ( unsigned i = 0; i < temp.size(); i++ )
				addCard( temp[i] );
		}
	}
	return matchPile.size() - initialNumberOfMatches;
}

bool Player::handSorted() const
{
	if ( hand.size() > 1 )
	{
		for ( unsigned i = 0; i < hand.size() - 1; i++ )
			if ( hand[ i + 1 ] < hand[i] )
				return false;
	}

	return true;
}

void Player::sortHand()
{
	while ( !handSorted() )
	{
		for ( unsigned i = 0; i < hand.size() - 1; i++ )
			if ( hand[ i + 1 ] < hand[ i ] )
				std::swap( hand[ i + 1 ], hand[ i ] );
	}
}