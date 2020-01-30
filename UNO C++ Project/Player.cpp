#include "pch.h"
#include "Player.h"
#include <string.h>

Player::Player() {} //pass by pointer, getDeck returns vector<Card> mydeck and from there adjust and change the values, then set it again.{}

void Player::setPlayerID(const int id) {

    m_ID = id; 
}

void Player::setPlayerName(const std::string name) {

    m_name = name;
}

void Player::drawStartingHand(Deck &deck) {

    for (uint8_t i = 0; i < START_HAND_SIZE; i++) {

        drawCard(deck);       
    }
}

void Player::drawCard(Deck &deck) {

    m_hand.push_back(deck.drawCardFromDeck());
}

void Player::showHand() {

    std::cout << "Player " << getPlayerName() << " hand" << std::endl;

    for (int i = 0; i < m_hand.size(); i++) {

        std::cout << i << "." << m_hand[i].getEnumColorToString() << " " << m_hand[i].getEnumSuitToString() << std::endl;
    }

    std::cout << std::endl;
}

Card Player::dropCardIntoPile(Deck &pile, bool &valid_card_flag, bool ignore_draw_flag) {

    int selection; 

    //Scenario: Player decides to not play a card, so he must draw one from deck
    if (ignore_draw_flag == true) {

        if (m_hand.back().getCardColour() == pile.getPile().back().getCardColour() || m_hand.back().getCardSuit() == pile.getPile().back().getCardSuit()
            || m_hand.back().getCardSuit() == Suit::WILD || m_hand.back().getCardSuit() == Suit::WILD_DRAW_FOUR) {

            std::cout <<"The card you have drawn matches the discard pile, so it must automatically be sent to the discard pile" << std::endl; 
            Card card = m_hand.back();
            pile.dropCardToPile(m_hand.back());
            m_hand.erase(m_hand.end()-1);
            pile.showPile();
            return card;
        }

        else {

            std::cout << "The card you have drawn does not match pile, so you must keep it" << std::endl; 
            return {};
        }
    }

    //Scenario: Player decides to drop a card, he may return to the menu if he makes a mistake
    std::cout << "Select a card to drop, type 900 to return" << std::endl;
    std::cin >> selection;

    if (((selection >= 0) && (selection <= m_hand.size()-1)) || (selection == 900)) {

        if (selection == 900) {

            std::cout << "Returning to player menu" << std::endl;
            return {};
        }

        else if (m_hand[selection].getCardColour() == pile.getPile().back().getCardColour() || m_hand[selection].getCardSuit() == pile.getPile().back().getCardSuit() ||
            m_hand[selection].getCardSuit() == Suit::WILD || m_hand[selection].getCardSuit() == Suit::WILD_DRAW_FOUR) {

            Card card = m_hand[selection];
            pile.dropCardToPile(m_hand[selection]);
            m_hand.erase(m_hand.begin() + selection);
            valid_card_flag = true;
            pile.showPile();
            return card;
        }
    }

    else {

        std::cout << "Card is invalid and cannot be placed on the pile, going back to player menu" << std::endl;
    }
};

void Player::setWildCardColor(Color color, Deck& pile) {

    pile.setTopPileCardColor(color);
}