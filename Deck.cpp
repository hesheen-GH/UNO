#include "Deck.h"
#include "Card.h"

Deck::Deck() {

    /* The deck consists of 108 cards: 4 each of "Wild" and "Wild Draw Four",
    Each color (red, yellow, green, blue) consists of 1 zero, 2 each of one through nine, and two each of "Skip", "Draw Two", and "Reverse". These last three types are known as "action cards". 
    */

	// populate all non-zero and non-wild cards, each containing 2 copies for each suit 
    for (int suit = static_cast<int>(Suit::ONE) ; suit < static_cast<int>(Suit::WILD_DRAW_FOUR); suit++) {

        for (int color = static_cast<int>(Color::RED); color < static_cast<int>(Color::NO_COLOR); color++) {
			
            m_deck.push_back(Card(static_cast<Color>(color), static_cast<Suit>(suit)));
            m_deck.push_back(Card(static_cast<Color>(color), static_cast<Suit>(suit)));
        }
    }

	// populate ZERO CARD AND WILD CARDS
    for (int color = static_cast<int>(Color::RED); color < static_cast<int>(Color::NO_COLOR); color++) {
		
        m_deck.push_back(Card(static_cast<Color>(color), Suit::ZERO));
        m_deck.push_back(Card(Color::NO_COLOR, Suit::WILD));
        m_deck.push_back(Card(Color::NO_COLOR, Suit::WILD_DRAW_FOUR)); 
    }

    std::cout << std::endl;
}

void Deck::restackDeck() {

    //copy all cards from the discard pile into the deck
    for (int i = 0; i < m_discardpile.size(); i++) {

        m_deck.push_back(m_discardpile[i]);
    }
    
    //delete all cards in the discard pile
    m_discardpile.clear(); 

    //restore used WILD_DRAW_FOUR and WILD cards to NO_COLOR so player can choose a color to set it to once activated
    for (auto it = m_deck.begin(); it != m_deck.end(); it++) {

        if (it->getCardSuit() == Suit::WILD_DRAW_FOUR || it->getCardSuit() == Suit::WILD) {

            it->setCardColour(Color::NO_COLOR);
        }
    }

    shuffleDeck();
    //must have one card in discard pile to keep game going
    setFirstCardToPile();
}

void Deck::shuffleDeck() {

    //RNG Seed time generated random shuffle of deck
    srand(time(0));
    std::random_shuffle(m_deck.begin(), m_deck.end());
}

void Deck::showDeck() {

    //reveals all contents of deck, useful for debugging purposes, not allowed for player use
    for (int i = 0; i < m_deck.size(); i++) {

        std::cout << "Card Number " << i << "is" << m_deck[i].getEnumColorToString() << " " << m_deck[i].getEnumSuitToString() << std::endl;
    }

    std::cout << std::endl; 
}

void Deck::showPile() {

    //reveals all contents of discard pile, allowed for player use
    std::cout << "This is the discard pile: " << std::endl;

    for (int i = 0; i < m_discardpile.size(); i++) {
	    
        std::cout << "Card Number " << i << "is" << m_discardpile[i].getEnumColorToString() << " " << m_discardpile[i].getEnumSuitToString() << std::endl;
    }

    std::cout << std::endl;
}

void Deck::setFirstCardToPile() {

    //copy back of deck to pile
    dropCardToPile(m_deck.back());
    
    if ((m_discardpile.back().getCardSuit() == Suit::WILD) || (m_discardpile.back().getCardSuit() == Suit::WILD_DRAW_FOUR)) {

        m_discardpile.back().setCardColour(static_cast<Color>(rand() % MAX_NUM_OF_COLORS));
    }
    //pop back of deck
    m_deck.pop_back();  
}

Card Deck::drawCardFromDeck() {

    //make sure deck is not empty, otherwise restack
    if (m_deck.size() == 0) {

        restackDeck();
    }

    Card card = m_deck.back();
    m_deck.pop_back();
    return card;
}

void Deck::dropCardToPile(Card card) {
	
    m_discardpile.push_back(card);
}

void Deck::setTopPileCardColor(const Color color) {

    //to be used for wild or wild_Draw_four
    m_discardpile.back().setCardColour(color);
}