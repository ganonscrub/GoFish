#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "Player.h"
#include "Deck.h"

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
	Game( unsigned numPlayers, bool hasAI = false );

	void run();

private:
	Deck deck;
	std::vector< Player > players;

	const bool hasAI;

	unsigned guesser;

	void dealCards();
	std::vector< Player >& getPlayers();
	
	void printPlayerHands(); //Used to print all player hands for testing
	void printPlayerMatchPile(unsigned playerNumber ) const;
	void printPlayerHand( unsigned playerNumber ) const;

	void guess( unsigned playerNumber );
	void computerGuess( unsigned playerNumber );
	void winner();

	unsigned numPlayers;
	const unsigned initialHandSize;
	unsigned cardsNotInPlay;
};

#endif