
#ifndef GAME_H
#define GAME_H
#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>

#include "Player.h"


using namespace std;

class Game
{

public:
	Game();
	int getNumOfPlayers();

	void shufflePlayers(vector<Player> &playerlist);
	void runTurn(vector<Player> &playerptr, Deck &deckptr, int i);
	void setInitialCardToPile(Deck &deckptr);
	void deletePlayer(vector<Player> &player, int i);
	void FirstPileCardEffect(vector<Player> &player, Deck &deckptr, int &iptr);

	void checkforWild(Deck &deckptr);
	bool checkforWildFour(vector<Player> &player, Deck &deckptr, int &iptr);
	bool checkforDrawTwo(vector<Player> &player, Deck &deckptr, int &iptr);
	bool checkforReverse(vector<Player> &player, Deck &deckptr);
	bool checkforSkip(vector<Player> &player, Deck &deckptr, int &iptr);

	void drawTwoCards(vector<Player> &player, Deck &deckptr, int &iptr, bool flag);
	void reversePlayers(vector<Player> &player, Deck &deckptr, int &iptr, bool flag);
	void skipPlayer(vector<Player> &player, Deck &deckptr, int &iptr, bool flag);
	void drawWildFourPlus(vector<Player> &player, Deck &deckptr, int &iptr, bool flag);
	

	

	void displayOtherPlayersHands(vector<Player> player, Deck deckptr, int iptr);

	void displayPlayerMenu(vector<Player> player, Deck deckptr, int iptr);

	bool checkWin(vector<Player> player);
};

#endif

