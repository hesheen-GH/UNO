#include "Game.h"
#include <iostream>

Game::Game()
{ 
    std::cout << "Welcome to UNO!" << std::endl;
    std::string player_name;

    m_players.resize(getNumOfPlayers()); 
    system("CLS"); 
    m_deck.shuffleDeck();

    //Starting Hand and player names
    for (int i = 0; i < m_players.size(); i++) {

        std::cout << "Please enter a name" << std::endl;
        std::cin >> player_name;
        m_players[i].setPlayerName(player_name);
        m_players[i].setPlayerID(i);
        m_players[i].drawStartingHand(m_deck);
    }

    shufflePlayers(); 
    std::cout << m_players[0].getPlayerName() << " will go first" << std::endl << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    system("CLS");
    m_deck.setFirstCardToPile();

    while (m_win == false) {

        for (auto it = m_players.begin(); it != m_players.end(); it++) {

            std::cout << "Please pass the display to " << it->getPlayerName() << " game will resume in" << std::endl;

            //pass interface to another player
            for (int timer = 3; timer > -1; timer--) {
                std::cout << timer << " seconds...\r";
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }

            startTurn(it);
            checkWin();
            system("CLS");
        }
    }
}

int Game::getNumOfPlayers() {

    int num_players = 0; //initalize
    bool flag = false;

    while (flag == false) {

	    std::cout << "Choose between 2-10 players" << std::endl;
	    std::cin >> num_players;
	    switch (num_players) {

            case 2:
	            flag = true;
	            break;
            case 3:
	            flag = true;
	            break;
            case 4:
	            flag = true;
	            break;
            case 5:
	            flag = true;
	            break;
            case 6:
	            flag = true;
	            break;
            case 7:
	            flag = true;
	            break;
            case 8:
	            flag = true;
	            break;
            case 9:
	            flag = true;
	            break;
            case 10:
	            flag = true;
	            break;
		    default: 
                std::cout << "Enter a valid number" << std::endl;
        }
    }
	
    return num_players;
}

void Game::shufflePlayers() {

    srand(time(0));
    std::random_shuffle(m_players.begin(), m_players.end());
}

/*void Game::deletePlayer(std::vector<Player>::iterator& it) {

    if (m_players.size() == MIN_NUM_OF_PLAYERS) {

        m_players.erase(it);
        m_win = true; 
        std::cout << "The match has ended and the remaining player" << m_players.back().getPlayerID() << "has won" << std::endl; 
    }

    else {

        m_players.erase(it);
        it--;
    }
}*/

void Game::runTurn(std::vector<Player>::iterator& it) {

	int user_choice;
	bool valid_card_flag = false;
    bool ignore_draw_flag = false; 
    Card card = {};

    displayPlayerMenu(it);
	std::cout << "Its  " << it->getPlayerName() << " 's turn" << std::endl;

	while (valid_card_flag == false) {

        std::cout << "What would you like to do? " << std::endl;
        std::cout << "0. Choose Card to drop to discard pile" << std::endl;
        std::cout << "1. Do Nothing and Draw a Card, if there is a match, you have to play that card" << std::endl;
        //std::cout << "2. Surrender" << std::endl;

        std::cin >> user_choice;

        switch (user_choice) {

		    case 0:
                card = it->dropCardIntoPile(m_deck, valid_card_flag, ignore_draw_flag);
                break;

		    case 1:
                ignore_draw_flag = true; 
                it->drawCard(m_deck);
                displayPlayerMenu(it);
                card = it->dropCardIntoPile(m_deck, valid_card_flag, ignore_draw_flag);
                ignore_draw_flag = false; 
                valid_card_flag = true;
                break;

		    /*case 2:
		    	std::cout << "Player " << it->getPlayerName() << "has left the game" << std::endl;
		    	deletePlayer(it);
		    	valid_card_flag = true;
		        break;*/

            default:
                std::cout << "Please enter a valid selection" << std::endl;
                break;      
        }
    }
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    endTurn(it, card);
}

void Game::checkWin() {

    for (auto it = m_players.begin(); it != m_players.end(); it++) {

	    switch (it->getHand().size()) {

            case 0:
                std::cout << "Winner winner chicken dinner, "<< it->getPlayerName() << " is the winner";
                std::this_thread::sleep_for(std::chrono::seconds(3));
                m_win = true;
                break;

		    default:
                break; //no winner
	    }
    }
}

void Game::Wild() {

    int choose_color;
    bool flag = false;

    std::cout << "Select a color to pick" << std::endl;
    std::cout << "0: Blue" << std::endl; 
    std::cout << "1: Red" << std::endl; 
    std::cout << "2: Green" << std::endl;
    std::cout << "3: Yellow" << std::endl;

    while (flag == false)
    {
        std::cin >> choose_color;
        switch (choose_color) {

            case 0:
                m_deck.setTopPileCardColor(Color::BLUE);
                flag = true;
                break;
            case 1:
                m_deck.setTopPileCardColor(Color::RED);
                flag = true;
                break;
            case 2:
                m_deck.setTopPileCardColor(Color::GREEN);
                flag = true;
                break;
            case 3:
                m_deck.setTopPileCardColor(Color::YELLOW);
                flag = true;
                break;
            default:
                std::cout << "Please select a valid color" << std::endl; 
        }
    }

    std::cout << "You have chosen " << m_deck.getPile().back().getEnumColorToString() << ". Please wait...." << std::endl ;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void Game::WildDrawFour(std::vector<Player>::iterator& it) {

    std::cout << it->getPlayerName() << "draws 4 cards and gets their turn skipped" << std::endl;
    it->drawCard(m_deck);  
    it->drawCard(m_deck);
    it->drawCard(m_deck);
    it->drawCard(m_deck);
    m_wildDrawFour = false;
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
}

void Game::DrawTwo(std::vector<Player>::iterator& it) {

    std::cout << it->getPlayerName() << "draws 2 cards and gets their turn skipped" << std::endl;
    it->drawCard(m_deck);
    it->drawCard(m_deck);
    m_drawTwo = false; 
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
}

void Game::Reverse(std::vector<Player>::iterator& it) {

    int i;
    int id = it->getPlayerID(); 
    std::reverse(m_players.begin(), m_players.end());
    std::cout << "Players have been reversed" << std::endl;

    for (i = 0; i < m_players.size(); i++) {

        if (m_players[i].getPlayerID() == id) {

            break;
        }
    }

    it = m_players.begin() + i; 
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
}
    
void Game::Skip(std::vector<Player>::iterator& it) {

    std::cout << it->getPlayerName() << " has been skipped" << std::endl; //wrong player , needs to be corrected
    m_skip = false;
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
}

void Game::displayOtherPlayersHands(std::vector<Player>::iterator it) {
    
    std::cout << "These are other player's hands" << std::endl;

    for (auto y = m_players.begin(); y != m_players.end(); y++) {

        if (y != it) {

            std::cout << y->getPlayerName() << " 's hand";
        }

        for (int x = 0; x < y->getHand().size(); x++) {

            if (y == it) {

                break;
            }
            std::cout << "X";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Game::displayPlayerMenu(std::vector<Player>::iterator it) {

    system("CLS");
    displayOtherPlayersHands(it);
    std::cout << std::endl << "There are " << m_deck.getDeck().size() << " cards remaining in the deck" << std::endl;
    m_deck.showPile();
    it->showHand();
}

void Game::startTurn(std::vector<Player>::iterator& it) {

    switch (m_deck.getPile().back().getCardSuit()) {

        case Suit::WILD_DRAW_FOUR:
            
            if (m_wildDrawFour == true) {

                WildDrawFour(it); 
            }

            else {

                runTurn(it);
            }

            break;

        case Suit::DRAW_TWO:

            if (m_drawTwo == true) {

                DrawTwo(it); 
            }
         
            else {

                runTurn(it);
            }

            break;

        case Suit::SKIP:

            if (m_skip == true) {

                Skip(it);
            }

            else {

                runTurn(it);
            }

            break;
 
        default:
            runTurn(it); 
            break;
    }
}

void Game::endTurn(std::vector<Player>::iterator& it, Card card) {

    switch (card.getCardSuit()) {

        case Suit::WILD:
            Wild();
            break;
        
        case Suit::WILD_DRAW_FOUR:
            Wild();
            m_wildDrawFour = true;
            break;

        case Suit::DRAW_TWO:
            m_drawTwo = true;
            break;

        case Suit::REVERSE:
            Reverse(it);
            break;

        case Suit::SKIP:
            m_skip = true;
            break;

        default: 
            break;
    }
}
