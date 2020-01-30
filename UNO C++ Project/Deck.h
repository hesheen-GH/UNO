#ifndef DECK_H
#define DECK_H
#pragma once

#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include "Card.h"

#define MIN_NUM_OF_PLAYERS 2
#define MAX_NUM_OF_COLORS 4

class Deck {

private:

	std::vector<Card> m_deck;
	std::vector<Card> m_discardpile;

public:

	Deck();
	void shuffleDeck();
	void showDeck();
	void showPile();
    std::vector<Card> getDeck() { return m_deck; }
    std::vector<Card> getPile() { return m_discardpile; }
	void restackDeck();
	void setFirstCardToPile();
	Card drawCardFromDeck();
	void dropCardToPile(Card card);
	void setTopPileCardColor(Color color);
};

#endif