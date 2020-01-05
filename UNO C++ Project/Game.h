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
#include "Deck.h"
#include "Card.h"


class Game {

private: 

    std::vector<Player> m_players;
    Deck m_deck; 
    Card m_topPileCard; 
    bool m_win = false;
    int m_turnCtr = 0; 

public:

	Game();
	int getNumOfPlayers();
	void shufflePlayers();
	void runTurn(std::vector<Player>::iterator it);
	void deletePlayer(std::vector<Player>::iterator& it);

    //checks
    void checkWin();
    void checkForWild();
	void checkForDrawTwo(std::vector<Player>::iterator& it);
	void checkForReverse();
	void checkForSkip(std::vector<Player>::iterator& it);
	void checkForWildDrawFour(std::vector<Player>::iterator& it);
	
    //displays
    void displayOtherPlayersHands(std::vector<Player>::iterator it);
    void displayPlayerMenu(std::vector<Player>::iterator it);
};

#endif
