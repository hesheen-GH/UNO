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
    bool m_win = false;
    bool m_wildDrawFour = false;
    bool m_drawTwo = false;
    bool m_reverse = false;
    bool m_skip = false; 
    

public:

    Game();
    int getNumOfPlayers();
    void shufflePlayers();
    void startTurn(std::vector<Player>::iterator& it);
    void runTurn(std::vector<Player>::iterator& it);
    void endTurn(std::vector<Player>::iterator& it, Card card);
    //void deletePlayer(std::vector<Player>::iterator& it);

    //checks
    void checkWin();

    //Card functions
    void Wild();
    void DrawTwo(std::vector<Player>::iterator& it);
    void Reverse(std::vector<Player>::iterator& it);
    void Skip(std::vector<Player>::iterator& it);
    void WildDrawFour(std::vector<Player>::iterator& it);
	
    //displays
    void displayOtherPlayersHands(std::vector<Player>::iterator it);
    void displayPlayerMenu(std::vector<Player>::iterator it);
};

#endif