#include "pch.h"
#include "Card.h"
#include <iostream>


#define DECK 108

using namespace std;


Card::Card(string set_color, string set_suit)
{
	color = set_color;
	suit = set_suit;
}

string Card::getCardColour()
{
	return color;
}

string Card::getCardType()
{
	return suit;
}

void Card::setCardColour(string temp) //used when a wild card/ wild four plus is played 
{
	color = temp;
}