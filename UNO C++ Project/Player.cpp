#include "pch.h"
#include "Player.h"


Player::Player() //pass by pointer, getDeck returns vector<Card> mydeck and from there adjust and change the values, then set it again.
{}


void Player::setPlayerID(string ID)
{
	player_ID = ID;
}

string Player::getPlayerID()
{
	return player_ID;
}

void Player::drawStartingHand(Deck &deckptr) {

	int i;

	for (i = 0; i < START_HAND; i++)
	{
		myhand.push_back(deckptr.drawCard());
	}

}

void Player::drawCard(Deck &deckptr)
{
	myhand.push_back(deckptr.drawCard());
};

void Player::showHand()
{
	int x;

	cout << "Player " << getPlayerID() << " hand" << endl;

	for (x = 0; x < myhand.size(); x++)

		cout << x << "." << myhand[x].getCardColour() << " " << myhand[x].getCardType() << endl;

	cout << endl;

};
void Player::dropCardIntoPile(Deck &deckptr, bool &validcardflag)
{
		int dropcard;
	
		cout << "Select a card to drop, type 900 to pass" << endl;
		cin >> dropcard;

				if (dropcard == 900) {

					goto pass;

				}

				else if (myhand[dropcard].getCardColour() == deckptr.getPile().back().getCardColour())
				{
					deckptr.discardCard(myhand[dropcard]);
					myhand.erase(myhand.begin() + dropcard);
					validcardflag = true;
				}

				else if (myhand[dropcard].getCardType() == deckptr.getPile().back().getCardType())
				{
					deckptr.discardCard(myhand[dropcard]);
					myhand.erase(myhand.begin() + dropcard);
					validcardflag = true;
				}

				else if (myhand[dropcard].getCardType() == "WILD")
				{
					deckptr.discardCard(myhand[dropcard]);
					myhand.erase(myhand.begin() + dropcard);
					validcardflag = true;
				}

				else if (myhand[dropcard].getCardType() == "WILD_DRAW_FOUR")
				{
					deckptr.discardCard(myhand[dropcard]);
					myhand.erase(myhand.begin() + dropcard);
					validcardflag = true;
				}

				else
				{
					cout << "Card is invalid" << endl;
				}

	pass: 

	
	deckptr.showPile();

};

vector<Card> Player::getHand()
{
	return myhand;
}