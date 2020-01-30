#include "Card.h"
#include <iostream>

Card::Card() {}

Card::~Card() {}

Card::Card(const Color color, const Suit suit) {

	m_color = color;
	m_suit = suit;
}

std::string Card::getEnumColorToString() {

    switch (m_color) {

        case RED:
            return "Red";  
        case BLUE:
            return "Blue";
        case GREEN:
            return "Green";
        case YELLOW:
            return "Yellow";
        case NO_COLOR:
            return "No Color";
        default:
            return "ERROR"; 
    }
}

std::string Card::getEnumSuitToString() {

    switch (m_suit) {

        case ONE:
            return "One";
        case TWO:
            return "Two";
        case THREE:
            return "Three";
        case FOUR:
            return "Four";
        case FIVE:
            return "Five";
        case SIX:
            return "Six";
        case SEVEN:
            return "Seven";
        case EIGHT:
            return "Eight";
        case NINE:
            return "Nine";
        case SKIP:
            return "Skip";
        case DRAW_TWO:
            return "Draw Two";
        case REVERSE:
            return "Reverse";
        case ZERO:
            return "Zero";
        case WILD: 
            return "Wild";
        case WILD_DRAW_FOUR:
            return "Wild Draw Four";
        default:
            return "ERROR";
    }
}

void Card::setCardColour(const Color color) {

	m_color = color;
}

