#include "Deck.h"
#include "Card.h"
#include <algorithm>
#include <random>

Deck::Deck() 
{
    for (int i = 1; i <= 13; ++i) {
        for (char s : {'s', 'c', 'd', 'h'}) {
            this->cards.emplace_back(i, s);
        }
    }
}

std::vector<Card>& Deck::getCards() {
    return this->cards;
}

void Deck::shuffle() 
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(cards.begin(), cards.end(), gen);
}

void Deck::printDeck() 
{
    for (const auto& card : cards) {
        card.printCard();
    }
}

const Card& Deck::getCardFromDeck(int index) const 
{
    /* Turned off to maximize speed
    if (index < 0 || index >= cards.size()) {
        throw std::out_of_range("Invalid index");
    } */
    return this->cards[index];
}