#ifndef CARD_H
#define CARD_H
#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>


using namespace std;

class Card
{
private:

	 string color;
	 string suit;

public:

	Card(string set_color, string set_suit);
	string getCardColour();
	string getCardType();
	void setCardColour(string temp);
};

#endif 