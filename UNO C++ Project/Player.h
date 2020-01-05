#ifndef PLAYER_H
#define PLAYER_H
#pragma once


#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "Deck.h"
#include "Card.h"

#define START_HAND_SIZE 7

class Player {

private:

    std::string m_ID; 
    std::vector<Card> m_hand;

public:

	Player();
    std::string getPlayerID() { return m_ID; } 
	void setPlayerID(const std::string ID);
	void drawStartingHand(Deck &deck);
	void drawCard(Deck &deck);
	void showHand(); //cout
    std::vector<Card> getHand() { return m_hand; }
	Card dropCardIntoPile(Deck& pile, bool &valid_card_flag, bool drop_drawn_card_flag);
    void setWildCardColor(Color color, Deck& pile);

};

#endif