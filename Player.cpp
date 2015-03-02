#include "Player.h"

Player::Player():matches(0){}

void Player::addCard( Card in )
{
	hand.push_back( in );
}
void Player::addMatches(std::vector<Card> in)
{
	matchPile.push_back(in);
	matches++;
}
void Player::printHand()
{
	for ( unsigned i = 0; i < hand.size(); i++ )
	{
		hand[i].printCard();
		std::cout << "\t";
	}
}
void Player::printMatchPile()
{
	for (unsigned i = 0; i < matchPile.size(); i++)
	{
		for (unsigned j = 0; j < 4; j++)
			matchPile[i][j].printCard();
		std::cout << "\t";
	}
}

bool Player::playerHasCard( Card test )
{
	for ( unsigned i = 0; i < hand.size(); i++ )
	{
		if ( hand[i]== test )
			return true;
	}
	return false;
}

std::vector< Card > Player::cardsOfRank( CARD_RANK targetRank )
{
	std::vector< Card > temp;
	for ( unsigned i = 0; i < hand.size(); i++ )
	{
		if ( hand[i].getRank() == targetRank )
		{
			temp.push_back( hand[i] );
			hand.erase( hand.begin() + i );
			i = -1;
		}
	}
	return temp;
}

unsigned Player::numCards()
{
	return hand.size();
}
int Player::get_numMatches()
{
	return matches;
}
int Player::get_rankAt(int index)
{
	return hand[index].getRank();
}