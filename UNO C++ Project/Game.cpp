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
	for (auto it = m_players.begin(); it != m_players.end(); it++) { 

		std::cout << "Please enter a name" << std::endl; 
		std::cin >> player_name;
		it->setPlayerID(player_name); 
		it->drawStartingHand(m_deck); 
	}   

	shufflePlayers(); 
	std::cout << m_players[0].getPlayerID() << " will go first" << std::endl << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	system("CLS");
    m_topPileCard = m_deck.setFirstCardToPile();

	while (m_win == false) {

        for (auto it = m_players.begin(); it != m_players.end(); it++) {

            checkForDrawTwo(it);
            checkForWildDrawFour(it);
            checkForReverse();
            checkForSkip(it);

            std::cout << "Please pass the display to " << it->getPlayerID() << " game will resume in" << std::endl;

            //pass interface to another player
            for (int timer = 3; timer > -1; timer--) {
                std::cout << timer << " seconds...\r";
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }

            displayPlayerMenu(it);
            runTurn(it);
            checkForWild();
            checkWin();
            system("CLS");
            m_turnCtr++;
        }
	}
}

int Game::getNumOfPlayers() {

	int num_players = 0; //initalize
	bool flag = false;

	while (flag == false)
	{
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

void Game::deletePlayer(std::vector<Player>::iterator& it) {

    if (m_players.size() == MIN_NUM_OF_PLAYERS) {

        m_players.erase(it);
        m_win = true; 
        std::cout << "The match has ended and the remaining player" << m_players.back().getPlayerID() << "has won" << std::endl; 
    }

    else {

        m_players.erase(it);
        it--;
    }
}

void Game::runTurn(std::vector<Player>::iterator it) {

	int user_choice;
	bool valid_card_flag = false;
    bool drop_drawn_card_flag = false; 

	std::cout << "Its  " << it->getPlayerID() << " 's turn" << std::endl;

	while (valid_card_flag == false) {

		std::cout << "What would you like to do? " << std::endl;
		std::cout << "0. Choose Card to drop to discard pile" << std::endl;
		std::cout << "1. Do Nothing and Draw a Card, if there is a match, you have a choice to play that card" << std::endl;
		std::cout << "2. Surrender" << std::endl;

		std::cin >> user_choice;

		switch (user_choice) {

		    case 0:
                m_topPileCard = it->dropCardIntoPile(m_deck, valid_card_flag, drop_drawn_card_flag);
			    break;

		    case 1:
                drop_drawn_card_flag = true; 
			    it->drawCard(m_deck);
			    displayPlayerMenu(it);
			    m_topPileCard = it->dropCardIntoPile(m_deck, valid_card_flag, drop_drawn_card_flag);
                drop_drawn_card_flag = false; 
                valid_card_flag = true;
			    break;

		    case 2:
		    	std::cout << "Player " << it->getPlayerID() << "has left the game" << std::endl;
		    	deletePlayer(it);
		    	valid_card_flag = true;
		        break;

		    default:
			    std::cout << "Please enter a valid selection" << std::endl;
			    break;
		}
	}

}

void Game::checkWin() {

	for (auto it = m_players.begin(); it != m_players.end(); it++) {

		switch (it->getHand().size()) {

		    case 0:
			    std::cout << "Winner winner chicken dinner, "<< it->getPlayerID() << " is the winner";
			    std::this_thread::sleep_for(std::chrono::seconds(3));
                m_win = true;
                break;

		    default:
			    break; //no winner
		}
	}
}

void Game::checkForWild() {

    // second condition for when it is the first turn and the first card in discard pile is a wild
    if (m_topPileCard.getCardSuit() == Suit::WILD || m_topPileCard.getCardSuit() == Suit::WILD_DRAW_FOUR) {

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

        m_topPileCard.setEmptyCard();
		std::cout << "You have chosen " << m_deck.getPile().back().getEnumColorToString() << ". Please wait...." << std::endl ;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

    else;
}

void Game::checkForWildDrawFour(std::vector<Player>::iterator& it) {

    while ((m_deck.getPile().back().getCardSuit() == Suit::WILD_DRAW_FOUR) && (m_turnCtr == 0)) {

        std::cout << "The First Pile card was a wild draw four so the deck has to be reshuffled and a new card placed in the pile" << std::endl;
        m_deck.restackDeck();
        m_topPileCard = m_deck.getPile().back(); 
    }

	if (m_topPileCard.getCardSuit() == Suit::WILD_DRAW_FOUR) {

		std::cout << it->getPlayerID() << "draws 4 cards and gets their turn skipped" << std::endl;
		it->drawCard(m_deck);  
        it->drawCard(m_deck);
        it->drawCard(m_deck);
        it->drawCard(m_deck);

        if (it == (m_players.end() - 1)) {

            it = m_players.begin(); //revert back to beginning of vector, otherwise data out of range
        }

        else {

            it++;
        }
		
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

    else;
}

void Game::checkForDrawTwo(std::vector<Player>::iterator& it) {

	if (m_topPileCard.getCardSuit() == Suit::DRAW_TWO) {
		
        std::cout << it->getPlayerID() << "draws 2 cards and gets their turn skipped" << std::endl;
		it->drawCard(m_deck);
        it->drawCard(m_deck);

        if (it == (m_players.end() - 1)) {

            it = m_players.begin(); //revert back to beginning of vector, otherwise data out of range
        }

        else {

            it++;
        }
        m_topPileCard.setEmptyCard();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

    else;
}

void Game::checkForReverse() {

	if (m_topPileCard.getCardSuit() == Suit::REVERSE) {

		std::cout << "Players have been reversed" << std::endl;
		std::reverse(m_players.begin(), m_players.end());
        m_topPileCard.setEmptyCard(); 
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

    else;
}
    
void Game::checkForSkip(std::vector<Player>::iterator& it) {

	if (m_topPileCard.getCardSuit() == Suit::SKIP) {

        if (it == (m_players.end()-1)) {

            it = m_players.begin(); //revert back to beginning of vector, otherwise data out of range
        }

        else {

            it++;
        }

		std::cout << it->getPlayerID() << " has been skipped" << std::endl;
        m_topPileCard.setEmptyCard();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}

    else;
}		

void Game::displayOtherPlayersHands(std::vector<Player>::iterator it) {
    
	std::cout << "These are other player's hands" << std::endl;

	for (auto y = m_players.begin(); y != m_players.end(); y++) {

        if (y != it) {

            std::cout << y->getPlayerID() << " 's hand";
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
	m_deck.showPile();
    it->showHand();
}
