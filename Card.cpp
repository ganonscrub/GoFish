#include "Card.h"
#include <Windows.h>

using namespace std;

void gotoxy(int x, int y)
{
	COORD coord;

	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	return;
}

Card::Card()
{
	cardRank = RANK_ACE;
	cardSuit = SUIT_SPADES;
}

Card::Card( CARD_RANK rank, CARD_SUIT suit ) : cardRank( rank ), cardSuit( suit )
{
	
}

CARD_RANK Card::get_rank() const
{
	return cardRank;
}

CARD_SUIT Card::get_suit() const
{
	return cardSuit;
}

void Card::set_rank( CARD_RANK newRank )
{
	cardRank = newRank;
}

void Card::set_suit( CARD_SUIT newSuit )
{
	cardSuit = newSuit;
}

bool Card::operator==( const Card& right ) const
{
	return ( cardSuit == right.cardSuit && cardRank == right.cardRank );
}

bool Card::operator<( const Card& right ) const // only cares about rank
{
	return static_cast<int>(cardRank) < static_cast<int>(right.cardRank);
}

ostream& operator<<(ostream& out, const Card& card)
{
	switch(card.cardSuit)
	{
	case SUIT_HEARTS:
	case SUIT_DIAMONDS:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
			FOREGROUND_RED|FOREGROUND_INTENSITY|BACKGROUND_BLUE|
			BACKGROUND_GREEN|BACKGROUND_RED|BACKGROUND_INTENSITY);
		break;
	case SUIT_CLUBS:
	case SUIT_SPADES:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
			BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED|
			BACKGROUND_INTENSITY);
		break;
	}
	switch(card.cardRank)
	{
	case RANK_ACE:
		out << "A";
		break;
	case RANK_TEN:
		out << "T";
		break;
	case RANK_JACK:
		out << "J";
		break;
	case RANK_QUEEN:
		out << "Q";
		break;
	case RANK_KING:
		out << "K";
		break;
	default:
		out << card.cardRank;
		break;
	}

	out << static_cast<char>(card.cardSuit);

	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7 );
	return out;
}

void Card::display_card( int x, int y, bool stacked, bool face_up ) const
{

	const char UPPER_LEFT = (const char)218;
	const char STACKED_UPPER_LEFT = (const char)195;
	const char STACKED_UPPER_RIGHT = (const char)180;
	const char UPPER_RIGHT = (const char)191;
	const char HORIZONTAL = (const char)196;
	const char VERTICAL = (const char)179;
	const char BOTTOM_LEFT = (const char)192;
	const char BOTTOM_RIGHT = (const char)217;

	//top line
	gotoxy( x, y );	
	if( stacked )
	{
		cout << STACKED_UPPER_LEFT;
	}
	else
	{
		cout << UPPER_LEFT;
	}
	for(int i=1; i<CARD_WIDTH-1; i++)
	{
		cout << HORIZONTAL;
	}
	if(stacked)
	{
		cout << STACKED_UPPER_RIGHT;
	}
	else
	{
		cout << UPPER_RIGHT;
	}
	
	//middle
	if(face_up)
	{
		for(int i=1; i<CARD_HEIGHT-1; i++)
		{
			gotoxy(x, y+i);
			cout << VERTICAL;
			if(i == 1) //first line
			{
				cout << *this;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE|
					BACKGROUND_GREEN|BACKGROUND_RED|BACKGROUND_INTENSITY);
				for(int j=3; j<CARD_WIDTH-1; j++)
				{
					cout << " ";
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			else if(i == CARD_HEIGHT - 2) // last line
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE|
					BACKGROUND_GREEN|BACKGROUND_RED|BACKGROUND_INTENSITY);
				for(int j=3; j<CARD_WIDTH-1; j++)
				{
					cout << " ";
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				cout << *this;
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_BLUE|
					BACKGROUND_GREEN|BACKGROUND_RED|BACKGROUND_INTENSITY);
				for(int j = 1; j<CARD_WIDTH-1; j++)
				{
					cout << " ";
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			cout << VERTICAL;
		}
	}
	else
	{
		for(int i=1; i<CARD_HEIGHT-1; i++)
		{
			gotoxy(x, y+i);
			cout << VERTICAL;
			for(int j = 1; j<CARD_WIDTH-1; j++)
			{
				cout << "*";
			}
			cout << VERTICAL;
		}
	}


	//bottom line
	gotoxy( x, y + CARD_HEIGHT - 1 );
	cout << BOTTOM_LEFT;
	for( int i = 1; i < CARD_WIDTH - 1; i++ )
	{
		cout << HORIZONTAL;
	}
	cout << BOTTOM_RIGHT;
	display_stamp( x, y );
}

char Card::rankToChar( CARD_RANK rank ) const
{
	switch ( rank )
	{
	case RANK_ACE:
		return 'A';
		break;
	case RANK_TEN:
		return 'T';
		break;
	case RANK_JACK:
		return 'J';
		break;
	case RANK_QUEEN:
		return 'Q';
		break;
	case RANK_KING:
		return 'K';
		break;
	default:
		return rank + 48;
		break;
	}
}

void Card::display_card_efficient( int x, int y ) const
{
	std::vector< std::string > lines( CARD_HEIGHT );

	for ( int i = 0; i < CARD_HEIGHT; i++ )
	{
		switch ( i )
		{
		case 0:
			for ( int j = 0; j < CARD_WIDTH; j++ )
			{
				if ( j == 0 )
					lines[i].push_back( UPPER_LEFT );
				else if ( j == CARD_WIDTH - 1 )
					lines[i].push_back( UPPER_RIGHT );
				else
					lines[i].push_back( HORIZONTAL );
			}
			break;
		case CARD_HEIGHT-1:
			for ( int j = 0; j < CARD_WIDTH; j++ )
			{
				if ( j == 0 )
					lines[i].push_back( BOTTOM_LEFT );
				else if ( j == CARD_WIDTH - 1 )
					lines[i].push_back( BOTTOM_RIGHT );
				else
					lines[i].push_back( HORIZONTAL );
			}
			break;
		default:
			for ( int j = 0; j < CARD_WIDTH; j++ )
			{
				if ( j == 0 || j == CARD_WIDTH - 1 )
					lines[i].push_back( VERTICAL );
				else
					lines[i].push_back( 219 );
			}
			break;
		}
	}

	for ( int i = 0; i < CARD_HEIGHT; i++ )
	{
		gotoxy( x, y + i );
		std::cout << lines[i].c_str();
	}
}

void Card::display_stamp(int x, int y) const
{

	switch( cardSuit )
	{
	case SUIT_HEARTS:
	case SUIT_DIAMONDS:
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE) , 
			FOREGROUND_RED|FOREGROUND_INTENSITY|BACKGROUND_BLUE|
			BACKGROUND_GREEN|BACKGROUND_RED|BACKGROUND_INTENSITY );
		break;
	case SUIT_CLUBS:
	case SUIT_SPADES:
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 
			BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_RED|
			BACKGROUND_INTENSITY );
		break;
	}

	if ( cardRank == 2 || cardRank == 3 )
	{
		gotoxy( x + CARD_WIDTH / 2, y + 2 );
		cout << static_cast<char>(cardSuit);
	}
	if ( cardRank > 3 && cardRank <= 10 )
	{
		gotoxy( x + 3, y + 2 );
		cout << static_cast<char>(cardSuit);
		gotoxy( x + CARD_WIDTH - 3, y + 2 );
		cout << static_cast<char>(cardSuit);
	}
	if (cardRank == 10 || cardRank == 8 || cardRank == 7)
	{
		gotoxy( x + CARD_WIDTH / 2, y + 3);
		cout << static_cast<char>(cardSuit);
	}
	if (cardRank == 9 || cardRank == 10 || cardRank == 7)
	{
		gotoxy( x + 3, y + 4 );
		cout << static_cast<char>(cardSuit);
		gotoxy( x + CARD_WIDTH - 3, y + 4 );
		cout << static_cast<char>(cardSuit);
	}
	if (cardRank == 8 || cardRank == 6)
	{
		gotoxy( x + 3, y + 5 );
		cout << static_cast<char>(cardSuit);
		gotoxy( x + CARD_WIDTH - 3, y + 5 );
		cout << static_cast<char>(cardSuit);
	}
	if (cardRank == 5 || cardRank == 3 || cardRank == 1 || cardRank == 9)
	{
		gotoxy( x + CARD_WIDTH / 2, y + 5);
		cout << static_cast<char>(cardSuit);
	}

	//left column
	//right column
	//middle

	//top
	//mid
	//bottom

	//10 and 8 are weird
	if ( cardRank == 9 || cardRank == 10)
	{
		gotoxy( x + 3, y + CARD_HEIGHT - 5);
		cout << static_cast<char>(cardSuit);
		gotoxy( x + CARD_WIDTH - 3, y + CARD_HEIGHT - 5);
		cout << static_cast<char>(cardSuit);
	}
	if (cardRank == 10 || cardRank == 8)
	{
		gotoxy( x + CARD_WIDTH / 2, y + CARD_HEIGHT - 4 );
		cout << static_cast<char>(cardSuit);
	}
	if (cardRank == 2 || cardRank == 3)
	{
		gotoxy( x + CARD_WIDTH / 2, y + CARD_HEIGHT - 3 );
		cout << static_cast<char>(cardSuit);
	}
	if ( cardRank > 3 && cardRank <= 10 )
	{
		gotoxy( x + 3, y + CARD_HEIGHT - 3 );
		cout << static_cast<char>(cardSuit);
		gotoxy( x + CARD_WIDTH - 3, y + CARD_HEIGHT - 3 );
		cout << static_cast<char>(cardSuit);
	}

	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 7 );

}