#include "Deck.h"
#include "Card.h"

Deck::Deck() {

    
	// all non-zero and non-wild cards, each containing 2 copies for each suit 
    for (uint8_t suit = static_cast<uint8_t>(Suit::ONE) ; suit < static_cast<int>(Suit::WILD_DRAW_FOUR); suit++) {

        for (uint8_t color = static_cast<uint8_t>(Color::RED); color < static_cast<int>(Color::NO_COLOR); color++) {
			
            m_deck.push_back(Card(static_cast<Color>(color), static_cast<Suit>(suit)));
            m_deck.push_back(Card(static_cast<Color>(color), static_cast<Suit>(suit)));
        }
    }

	// ZERO CARD AND WILD CARDS
    for (uint8_t color = static_cast<uint8_t>(Color::RED); color < static_cast<uint8_t>(Color::NO_COLOR); color++) {
		
        m_deck.push_back(Card(static_cast<Color>(color), Suit::ZERO));
        m_deck.push_back(Card(Color::NO_COLOR, Suit::WILD));
        m_deck.push_back(Card(Color::NO_COLOR, Suit::WILD_DRAW_FOUR)); 
    }

    std::cout << std::endl;
}

void Deck::restackDeck() {

    for (int i = 0; i < m_discardpile.size(); i++) {

        m_deck.push_back(m_discardpile[i]);
    }
    
    m_discardpile.clear();

    for (auto it = m_deck.begin(); it != m_deck.end(); it++) {

        if (it->getCardSuit() == Suit::WILD_DRAW_FOUR || it->getCardSuit() == Suit::WILD) {

            it->setCardColour(Color::NO_COLOR);
        }
    }

    shuffleDeck();
    m_discardpile.push_back(m_deck.back()); //must havce one card in discard pile

    if ((m_discardpile.back().getCardSuit() == Suit::WILD) || (m_discardpile.back().getCardSuit() == Suit::WILD_DRAW_FOUR)) {

        m_discardpile.back().setCardColour(static_cast<Color>(rand() % MAX_NUM_OF_COLORS));
    }
}

void Deck::shuffleDeck() {

    srand(time(0));
    random_shuffle(m_deck.begin(), m_deck.end());
}

void Deck::showDeck() {

    for (int i = 0; i < m_deck.size(); i++) {

	    std::cout << "Card Number " << i << "is" << m_deck[i].getEnumColorToString() << " " << m_deck[i].getEnumSuitToString() << std::endl;
    }

    std::cout << std::endl; // try setting m_booleans here
}

void Deck::showPile() {

    std::cout << "This is the discard pile: " << std::endl;

    for (int i = 0; i < m_discardpile.size(); i++)
    {
	    std::cout << "Card Number " << i << "is" << m_discardpile[i].getEnumColorToString() << " " << m_discardpile[i].getEnumSuitToString() << std::endl;
    }

    std::cout << std::endl;
}

void Deck::setFirstCardToPile() {

    m_discardpile.push_back(m_deck.back()); 
    
    if ((m_discardpile.back().getCardSuit() == Suit::WILD) || (m_discardpile.back().getCardSuit() == Suit::WILD_DRAW_FOUR)) {

        m_discardpile.back().setCardColour(static_cast<Color>(rand() % MAX_NUM_OF_COLORS));
    }
    //begin game
    m_deck.pop_back();  
}

Card Deck::drawCardFromDeck() {

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

void Deck::setTopPileCardColor(Color color) {

    m_discardpile.back().setCardColour(color);
}