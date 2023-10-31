#pragma once
#ifndef FAST_DECK_H
#define FAST_DECK_H

#include <vector>

class FastDeck {
private:
    std::vector<int> cardValues;
    int DECK_MULT = 100; // Describes how many individual decks should be in the FastDeck object
public:
    FastDeck(); // Constructor declaration
    std::vector<int>& getCardValues(); // Declaration for getCardValues
    void shuffle(); // Method declarations
    void replenish(); 
    void printDeck();
    int getCardValueFromIndex(int index) const;
    int dealCard();
};

#endif // FAST_DECK_H
