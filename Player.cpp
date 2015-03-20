#include "Player.h"
#include <Windows.h>

Player::Player( bool isAI ) : AIPlayer( isAI )
{
}

int Player::get_numMatches() const
{
	return matchPile.size();
}
CARD_RANK Player::get_rankAt(int index) const
{
	return hand[index].get_rank();
}

void Player::printHand() const
{
	for ( unsigned i = 0; i < hand.size(); i++ )
		hand[i].display_card( i + ( i * 2 ), 3 );
}

void Player::printHand( unsigned posX, unsigned posY ) const
{
	for ( unsigned i = 0; i < hand.size(); i++ )
		hand[i].display_card( i + ( i * 2 ) + posX, posY );
}

void Player::printHandWithSelection( unsigned posX, unsigned posY, unsigned selectedIndex ) const
{
	for ( int i = -1; i < CARD_HEIGHT; i++ )
	{
		gotoxy( posX, posY + i );
		std::cout << "                                                            ";
	}
	for ( unsigned i = 0; i < hand.size(); i++ )
	{
		if ( i != selectedIndex )
			hand[i].display_card( i * CARD_WIDTH + posX - ( i * 9 ), posY );
		else
			hand[i].display_card( i * CARD_WIDTH + posX - ( i * 9 ), posY - 1 );
	}
}

void Player::printHandNew( unsigned posX, unsigned posY ) const
{
	if ( hand.size() == 0 )
		return;
	else if ( hand.size() == 1 )
	{
		return;
	}
	else
	{
		for ( int i = 0; i < hand.size(); i++ )
		{
			for ( int j = 0; j < CARD_HEIGHT; j++ )
			{
				gotoxy( posX + ( 3 * i ), posY + j );
				if ( i < hand.size() - 1 )
				{
					for ( int k = 0; k < 3; k++ )
					{
						if ( j == 0 && k % 3 == 0 )
							std::cout << UPPER_LEFT;
						else if ( j == CARD_HEIGHT - 1 && k % 3 == 0 )
							std::cout << BOTTOM_LEFT;
						else if ( j == 0 || j == CARD_WIDTH - 1 )
							std::cout << HORIZONTAL;
						else
						{
							if ( j == 1 )
							{
								if ( k == 0 || k == CARD_WIDTH - 1 )
									std::cout << VERTICAL;
								else if ( k == 1 )
									std::cout << hand[i].rank_char();
								else if ( k == 2 )
									std::cout << (char)hand[i].get_suit();
								else
									std::cout << "X";
							}
							else
							{
								if ( k % 3 == 0 )
									std::cout << VERTICAL;
							}
						}
					}
				}
				else
				{
					for ( int k = 0; k < CARD_WIDTH; k++ )
					{
						if ( j == 0 && k == 0 )
							std::cout << UPPER_LEFT;
						else if ( j == 0 && k == CARD_WIDTH - 1 )
							std::cout << UPPER_RIGHT;
						else if ( j == CARD_HEIGHT - 1 && k == 0 )
							std::cout << BOTTOM_LEFT;
						else if ( j == CARD_HEIGHT - 1 && k == CARD_WIDTH - 1 )
							std::cout << BOTTOM_RIGHT;
						else if ( j == 0 && k == CARD_WIDTH - 1 )
							std::cout << UPPER_RIGHT;
						else if ( j == 0 && k > 0 && k < CARD_WIDTH - 1 )
							std::cout << HORIZONTAL;
						else if ( j == CARD_HEIGHT - 1 && k > 0 && k < CARD_WIDTH - 1 )
							std::cout << HORIZONTAL;
						else if ( j > 0 && j < CARD_HEIGHT - 1 && k == 0 )
							std::cout << VERTICAL;
						else if ( j > 0 && j < CARD_HEIGHT - 1 && k == CARD_WIDTH - 1 )
							std::cout << VERTICAL;
						else if ( j == 1 && k == 1 )
							std::cout << hand[i].rank_char();
						else if ( j == 1 && k == 2 )
							std::cout << (char)hand[i].get_suit();
						else if ( j == CARD_HEIGHT - 2 && k == CARD_WIDTH - 3 )
							std::cout << hand[i].rank_char();
						else if ( j == CARD_HEIGHT - 2 && k == CARD_WIDTH - 2 )
							std::cout << (char)hand[i].get_suit();
						else
							std::cout << ' ';
					}
				}
			}
		}
	}
}

void Player::printHandNewWithSelection( unsigned posX, unsigned posY, unsigned selectedIndex ) const
{
	if ( hand.size() == 0 )
		return;
	else if ( hand.size() == 1 )
	{
		return;
	}
	else
	{
		for ( int i = 0; i < hand.size(); i++ )
		{
			for ( int j = 0; j < CARD_HEIGHT; j++ )
			{
				if ( i == selectedIndex )
					gotoxy( posX + ( 3 * i ), posY + j - 1 );
				else
					gotoxy( posX + ( 3 * i ), posY + j );

				if ( i < hand.size() - 1 )
				{
					if ( i == selectedIndex )
					{
						if ( j > 0 )
						{
							for ( int k = 0; k < 3; k++ )
							{
								if ( j == 0 && k % 3 == 0 )
									std::cout << UPPER_LEFT;
								else if ( j == CARD_HEIGHT - 1 && k % 3 == 0 )
									std::cout << BOTTOM_LEFT;
								else if ( j == 0 || j == CARD_WIDTH - 1 )
									std::cout << HORIZONTAL;
								else
								{
									if ( j == 1 )
									{
										if ( k == 0 || k == CARD_WIDTH - 1 )
											std::cout << VERTICAL;
										else
										{
											setConBySuit( hand[i].get_suit() );

											if ( k == 1 )
												std::cout << hand[i].rank_char();
											else if ( k == 2 )
												std::cout << (char)hand[i].get_suit();

											setConNorm();
										}
									}
									else
									{
										if ( k % 3 == 0 )
											std::cout << VERTICAL;
										else
										{
											setConBySuit( hand[i].get_suit() );
											std::cout << ' ';
											setConNorm();
										}
									}
								}
							}
						}
						else
						{
							for ( int k = 0; k < CARD_WIDTH; k++ )
							{
								if ( k == 0 )
									std::cout << UPPER_LEFT;
								else if ( k > 0 && k < CARD_WIDTH - 1 )
									std::cout << HORIZONTAL;
								else
									std::cout << UPPER_RIGHT;
							}							
						}
						if ( selectedIndex >= 0 )
						{
							gotoxy( posX + ( 3 * i ), posY + 11 );
							if ( selectedIndex == 0 )
							{
								std::cout << "   ";
								gotoxy( posX + ( 3 * hand.size() ) - 3, posY - 1 );
								std::cout << "            ";
							}
							else
								std::cout << BOTTOM_RIGHT << "  ";
							gotoxy( posX + ( 3 * i ) - 3, posY - 1 );
							std::cout << "   ";
							gotoxy( posX + ( 3 * i ) + 12, posY - 1 );
							std::cout << "   ";
						}
					}
					else
					{
						for ( int k = 0; k < 3; k++ )
						{
							if ( j == 0 && k % 3 == 0 )
								std::cout << UPPER_LEFT;
							else if ( j == CARD_HEIGHT - 1 && k % 3 == 0 )
								std::cout << BOTTOM_LEFT;
							else if ( j == 0 || j == CARD_WIDTH - 1 )
								std::cout << HORIZONTAL;
							else
							{
								if ( j == 1 )
								{
									if ( k == 0 || k == CARD_WIDTH - 1 )
										std::cout << VERTICAL;
									else
									{
										setConBySuit( hand[i].get_suit() );

										if ( k == 1 )
											std::cout << hand[i].rank_char();
										else if ( k == 2 )
											std::cout << (char)hand[i].get_suit();

										setConNorm();
									}
								}
								else
								{
									if ( k % 3 == 0 )
										std::cout << VERTICAL;
									else
									{
										setConBySuit( hand[i].get_suit() );
										std::cout << ' ';
										setConNorm();
									}
								}
							}
						}
					}
				}
				else
				{
					for ( int k = 0; k < CARD_WIDTH; k++ )
					{
						if ( j == 0 && k == 0 )
							std::cout << UPPER_LEFT;
						else if ( j == 0 && k == CARD_WIDTH - 1 )
							std::cout << UPPER_RIGHT;
						else if ( j == CARD_HEIGHT - 1 && k == 0 )
							std::cout << BOTTOM_LEFT;
						else if ( j == CARD_HEIGHT - 1 && k == CARD_WIDTH - 1 )
							std::cout << BOTTOM_RIGHT;
						else if ( j == 0 && k == CARD_WIDTH - 1 )
							std::cout << UPPER_RIGHT;
						else if ( j == 0 && k > 0 && k < CARD_WIDTH - 1 )
							std::cout << HORIZONTAL;
						else if ( j == CARD_HEIGHT - 1 && k > 0 && k < CARD_WIDTH - 1 )
							std::cout << HORIZONTAL;
						else if ( j > 0 && j < CARD_HEIGHT - 1 && k == 0 )
							std::cout << VERTICAL;
						else if ( j > 0 && j < CARD_HEIGHT - 1 && k == CARD_WIDTH - 1 )
							std::cout << VERTICAL;
						else
						{
							setConBySuit( hand[i].get_suit() );

							if ( j == 1 && k == 1 )
								std::cout << hand[i].rank_char();
							else if ( j == 1 && k == 2 )
								std::cout << (char)hand[i].get_suit();
							else if ( j == CARD_HEIGHT - 2 && k == CARD_WIDTH - 3 )
								std::cout << hand[i].rank_char();
							else if ( j == CARD_HEIGHT - 2 && k == CARD_WIDTH - 2 )
								std::cout << (char)hand[i].get_suit();
							else
								std::cout << ' ';

							setConNorm();
						}
					}

					if ( selectedIndex > 0 )
					{
						gotoxy( posX + ( 3 * i ), posY + 11 );
						std::cout << BOTTOM_LEFT;
					}
					if ( i == selectedIndex )
					{
						gotoxy( posX, posY - 1 );
						std::cout << "            ";

						gotoxy( posX + ( 3 * i ), posY + 11 );
						std::cout << BOTTOM_RIGHT << "           ";
						
						gotoxy( posX + ( 3 * i ) - 3, posY - 1 );
						std::cout << "   ";
					}
				}
			}
		}
	}
}

void Player::printMatchPile() const
{
	for ( unsigned i = 0; i < matchPile.size(); i++ )
		matchPile[i][0].display_card( i * CARD_WIDTH + 8 - ( i * 10 ), 18 );
}

void Player::printMatchPile( unsigned posX, unsigned posY ) const
{
	for ( unsigned i = 0; i < matchPile.size(); i++ )
		matchPile[i][0].display_card( i * CARD_WIDTH + posX - ( i * 10 ), posY );
}

int Player::numCards() const
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
	for ( int i = 0; i < numCards(); i++ )
	{
		std::vector< Card > temp = cardsOfRank( get_rankAt( i ) );
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

Card Player::cardAt( unsigned index ) const
{
	if ( index >= 0 && index < hand.size() )
		return hand[index];
	else
		return Card( static_cast<CARD_RANK>(-1), static_cast<CARD_SUIT>(-1) );
}

bool Player::isAI() const
{
	return AIPlayer;
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

void Player::setConNorm() const
{
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7 );
}
void Player::setConRed() const
{
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE) , 
			FOREGROUND_RED|FOREGROUND_INTENSITY|BACKGROUND_BLUE|
			BACKGROUND_GREEN|BACKGROUND_RED|BACKGROUND_INTENSITY );
}
void Player::setConBlack() const
{
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 
			BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED|
			BACKGROUND_INTENSITY );
}

void Player::setConBySuit( CARD_SUIT inSuit ) const
{
	if ( inSuit == SUIT_CLUBS || inSuit == SUIT_SPADES )
		setConBlack();
	else if ( inSuit == SUIT_HEARTS || inSuit == SUIT_DIAMONDS )
		setConRed();
}