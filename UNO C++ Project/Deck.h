#pragma once

#ifndef DECK_H
#define DECK_H

#include <string>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include "Card.h"


#define DECK 108

using namespace std;

class Deck
{

private:

	int color_INDX, suit_INDX;
	string color, suit;
	vector<Card> mydeck;
	vector<Card> discardpile;

public:

	Deck();
	void shuffleDeck();
	void showAllDeck();
	void showPile();
	vector<Card> getDeck();
	vector<Card> getPile();
	void setDeck(vector<Card> temp);
	void setPile(vector<Card> temp);
	void restackDeck();

	void setFirstCardToPile();
	Card drawCard();
	void discardCard(Card discarded_card);
	void setWildCardColor(string wildcard);
};

#endif 
