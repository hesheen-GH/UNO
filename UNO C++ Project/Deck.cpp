#include "pch.h"
#include "Deck.h"


Deck::Deck()
{
	// ALL NON ZERO AND NON WILD CARDS

	for (suit_INDX = 1; suit_INDX < 13; suit_INDX++)
	{
		switch (suit_INDX)
		{
		case 1: suit = "ONE"; break;
		case 2: suit = "TWO"; break;
		case 3: suit = "THREE"; break;
		case 4: suit = "FOUR"; break;
		case 5: suit = "FIVE"; break;
		case 6: suit = "SIX"; break;
		case 7: suit = "SEVEN"; break;
		case 8: suit = "EIGHT"; break;
		case 9: suit = "NINE"; break;
		case 10: suit = "SKIP"; break;
		case 11: suit = "DRAW_TWO"; break;
		case 12: suit = "REVERSE"; break;
		}

		for (color_INDX = 0; color_INDX < 4; color_INDX++)
		{
			switch (color_INDX)
			{
			case 0: color = "RED"; break;
			case 1: color = "BLUE"; break;
			case 2: color = "GREEN"; break;
			case 3: color = "YELLOW"; break;
			}

			mydeck.push_back(Card(color, suit));
			mydeck.push_back(Card(color, suit));
		}
	}

	// ZERO CARD AND WILD CARDS

	for (color_INDX = 0; color_INDX < 4; color_INDX++)
	{
		switch (color_INDX)
		{
		case 0: color = "RED"; break;
		case 1: color = "BLUE"; break;
		case 2: color = "GREEN"; break;
		case 3: color = "YELLOW"; break;
		default: cout << "Hello" << endl;

		}
		mydeck.push_back(Card(color, "ZERO"));
		mydeck.push_back(Card("NO_COLOR", "WILD"));
		mydeck.push_back(Card("NO_COLOR", "WILD_DRAW_FOUR")); //temp
	}

	cout << endl;
}



void Deck::restackDeck()
{
	discardpile.clear();
	Deck(); //create new deck
	shuffleDeck();
	discardpile.push_back(mydeck.back());
}

void Deck::shuffleDeck()
{
	srand(time(0));
	random_shuffle(mydeck.begin(), mydeck.end());
}

void Deck::showAllDeck()

{
	int temp;

	for (temp = 0; temp < mydeck.size(); temp++)
	{
		cout << "Card Number " << temp << "is" << mydeck[temp].getCardColour() << " " << mydeck[temp].getCardType() << endl;
	}

	cout << endl;
}

void Deck::showPile()
{
	int temp;

	cout << "This is the discard pile: " << endl;

	for (temp = 0; temp < discardpile.size(); temp++)
	{
		cout << "Card Number " << temp << "is" << discardpile[temp].getCardColour() << " " << discardpile[temp].getCardType() << endl;
	}

	cout << endl;
}


vector<Card> Deck::getDeck() 
{
	return mydeck;
}

vector<Card> Deck::getPile() {

	return discardpile;
}

void Deck::setDeck(vector<Card> temp) 
{
	mydeck = temp;
}

void Deck::setPile(vector<Card> temp) 
{
	discardpile = temp;
}

void Deck::setFirstCardToPile() //begin game
{
	discardpile.push_back(mydeck.back());
}

Card Deck::drawCard() 
{
	if (mydeck.size() == 0)
	{
		restackDeck();
	}

	Card drawn_card = mydeck.back();
	mydeck.pop_back();
	return drawn_card;
}

void Deck::discardCard(Card discarded_card) 
{
	discardpile.push_back(discarded_card);
}

void Deck::setWildCardColor(string wildcard) {

	discardpile.back().setCardColour(wildcard);
}