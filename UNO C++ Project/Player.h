#pragma once
#ifndef PLAYER_H
#define PLAYER_H


#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "Deck.h"
#include "Card.h"

#define DECK 108
#define START_HAND 7

using namespace std;

class Player : public Deck
{

private:

	string player_ID;

	vector<Card> myhand;

public:

	//Player(Deck *deck);
	Player();

	string getPlayerID();
	void setPlayerID(string ID);
	void drawStartingHand(Deck &deckptr);
	void drawCard(Deck &deckptr);
	void showHand(); //cout
	vector<Card> getHand();
	void dropCardIntoPile(Deck &deckptr, bool &validcardflag);

	//void dropCard();

};

#endif