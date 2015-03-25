#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "Player.h"
#include "Deck.h"
#include <Windows.h>

const unsigned KEY_ENTER = 13;
const unsigned KEY_LEFT = 75;
const unsigned KEY_RIGHT = 77;

const unsigned positionPlayerLabelX = 5; // text displaying current player number
const unsigned positionPlayerLabelY = 3;

const unsigned positionPlayerHandX = positionPlayerLabelX; // where to start drawing current player's hand
const unsigned positionPlayerHandY = positionPlayerLabelY + 5;

const unsigned positionPlayerMatchX = positionPlayerHandX; // where to start drawing current player's matches
const unsigned positionPlayerMatchY = positionPlayerHandY + 15;

const unsigned positionAcquiredCardX = positionPlayerMatchX + 70; // where to start drawing cards drawn from deck/taken from players
const unsigned positionAcquiredCardY = positionPlayerMatchY;

const unsigned positionTargetPlayerX = positionPlayerMatchX; // where to start drawing "Target player: " prompt
const unsigned positionTargetPlayerY = positionPlayerMatchY + 15;

const unsigned positionGuessRankX = positionTargetPlayerX; // where to start drawing "Guess rank: " prompt
const unsigned positionGuessRankY = positionTargetPlayerY + 1;

const unsigned positionCardsLeftInPlayX = 98;
const unsigned positionCardsLeftInPlayY = positionPlayerLabelY;

const unsigned positionWinnersX = 50;
const unsigned positionWinnersY = 20;

class Game
{
public:
	Game( unsigned numOfRealPlayers, unsigned numOfAIPlayers, unsigned numPlayers, bool isAIGame );

	void run();

private:
	Deck deck;
	std::vector< Player > players;

	const bool isAIGame;

	unsigned guesser;

	void dealCards();
	std::vector< Player >& getPlayers();
	
	void printPlayerMatchPile(unsigned playerNumber ) const;
	//void printPlayerHand( unsigned playerNumber ) const; function not needed
	void printGameInfo() const;

	void guess( unsigned playerNumber );
	void computerGuess( unsigned playerNumber );
	void checkForMatches( unsigned targetPlayer, CARD_RANK guessedRank, unsigned playerGuessing );
	void winner();
	unsigned numPlayers;
	unsigned numOfRealPlayers;
	unsigned numOfAIPlayers;
	const unsigned initialHandSize;
	unsigned cardsNotInPlay;
};

#endif