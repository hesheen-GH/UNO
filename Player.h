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

    std::string m_name;
    int m_ID;
    std::vector<Card> m_hand;

public:

    Player();
    std::string getPlayerName() { return m_name; } 
    int getPlayerID() { return m_ID; }
    void setPlayerName(const std::string name);
    void setPlayerID(const int id);
    void drawStartingHand(Deck &deck);
    void drawCard(Deck &deck);
    void showHand(); //cout
    std::vector<Card> getHand() { return m_hand; }
    Card dropCardIntoPile(Deck& pile, bool &valid_card_flag, bool ignore_draw_flag);
    void setWildCardColor(Color color, Deck& pile);
};

#endif