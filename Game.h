#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "Player.h"
#include "Deck.h"

const unsigned KEY_ENTER = 13;
const unsigned KEY_LEFT = 75;
const unsigned KEY_RIGHT = 77;
const unsigned playerLabelX = 5; // text displaying current player number
const unsigned playerLabelY = 3;

const unsigned playerHandX = playerLabelX; // where to start drawing current player's hand
const unsigned playerHandY = playerLabelY + 3;

const unsigned playerMatchX = playerLabelX; // where to start drawing current player's matches
const unsigned playerMatchY = playerLabelY + 18;

const unsigned acquiredCardX = playerMatchX + 70; // where to start drawing cards drawn from deck/taken from players
const unsigned acquiredCardY = playerMatchY;

const unsigned targetPlayerX = playerMatchX; // where to start drawing "Target player: " prompt
const unsigned targetPlayerY = playerMatchY + 17;

const unsigned guessRankX = targetPlayerX; // where to start drawing "Guess rank: " prompt
const unsigned guessRankY = targetPlayerY + 1;

const unsigned cardsLeftInPlayX = 98;
const unsigned cardsLeftInPlayY = playerLabelY;

const unsigned winnersX = 50;
const unsigned winnersY = 20;

class Game
{
public:
	Game(unsigned numOfRealPlayers, unsigned numOfAIPlayers, unsigned numPlayers, bool isAIGame);

	void run();

private:
	Deck deck;
	std::vector< Player > players;

	const bool isAIGame;

	unsigned guesser;

	void dealCards();
	std::vector< Player >& getPlayers();
	
	void printPlayerMatchPile(unsigned playerNumber ) const;
	void printPlayerHand( unsigned playerNumber ) const;

	void guess( unsigned playerNumber );
	void computerGuess( unsigned playerNumber );
	void checkForMatches(unsigned guesser, unsigned targetPlayer, CARD_RANK guessedRank, unsigned playerGuessing);
	void winner();
	unsigned numPlayers;
	unsigned numOfRealPlayers;
	unsigned numOfAIPlayers;
	const unsigned initialHandSize;
	unsigned cardsNotInPlay;
};

#endif