#ifndef CARD_H
#define CARD_H
#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

enum Color {

    RED = 0,
    BLUE,
    GREEN,
    YELLOW,
    NO_COLOR,
};

enum Suit {

    ONE = 0,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    SKIP,
    DRAW_TWO,
    REVERSE,
    WILD_DRAW_FOUR,
    WILD,
    ZERO,
    NO_SUIT
};

class Card {

private:

     Color m_color;
     Suit m_suit;

public:

    Card();
    ~Card(); 
	Card(const Color color, const Suit suit);
    std::string getEnumColorToString();
    std::string getEnumSuitToString();
    Color getCardColour() { return m_color; }
    Suit getCardSuit() { return m_suit;  }
	void setCardColour(const Color color);
    void setEmptyCard();
};

#endif 