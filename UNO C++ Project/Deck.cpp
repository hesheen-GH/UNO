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
    shuffleDeck();
	m_discardpile.push_back(m_deck.back()); //must havce one card in discard pile
}

void Deck::shuffleDeck() {

	srand(time(0));
	random_shuffle(m_deck.begin(), m_deck.end());
}

void Deck::showDeck() {

	for (uint8_t i = 0; i < m_deck.size(); i++)
	{
		std::cout << "Card Number " << i << "is" << m_deck[i].getEnumColorToString() << " " << m_deck[i].getEnumSuitToString() << std::endl;
	}
	std::cout << std::endl;
}

void Deck::showPile() {

	std::cout << "This is the discard pile: " << std::endl;

	for (uint8_t i = 0; i < m_discardpile.size(); i++)
	{
		std::cout << "Card Number " << i << "is" << m_discardpile[i].getEnumColorToString() << " " << m_discardpile[i].getEnumSuitToString() << std::endl;
	}
	std::cout << std::endl;
}

void Deck::setDeck(std::vector<Card> deck) {

	m_deck = deck;
}

void Deck::setPile(std::vector<Card> pile) {

	m_discardpile = pile;
}


Card Deck::setFirstCardToPile() {

    m_discardpile.push_back(m_deck.back()); //begin game
    m_deck.pop_back();  
    return m_discardpile.back(); 
}

Card Deck::drawCardFromDeck() {

	if (m_deck.size() == 0) {

		restackDeck();
	}

	Card card = m_deck.back();
	m_deck.pop_back();
	return card;
}

void Deck::dropCardToPile(Card card) 
{
	m_discardpile.push_back(card);
}

void Deck::setTopPileCardColor(Color color) {

	m_discardpile.back().setCardColour(color);
}