#ifndef CARD_H
#define CARD_H
#pragma once

#include <string>

//Color enumerations. UNO has 4 different colors. NO_COLOR is used for WILD_DRAW_FOUR and WILD cards
enum Color {

    RED = 0,
    BLUE,
    GREEN,
    YELLOW,
    NO_COLOR,
};

//Suit enumerations. UNO has a variety of different cards, including number, skip, reverse, draw +2 and +4 cards. 
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
};

#endif 