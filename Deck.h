#pragma once
// Deck.h
#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"

class Deck 
{
private:
    std::vector<Card> cards; 

public:
    Deck(); // Constructor declaration
    std::vector<Card>& getCards(); // Declaration for getCards
    void shuffle(); // Method declarations
    void printDeck();
    const Card& getCardFromDeck(int index) const; 
};

#endif // DECK_H
