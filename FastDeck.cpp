#include "FastDeck.h"
#include <algorithm>
#include <random>
#include <iostream>

/* Fast deck is similar to Deck but instead of Cards, it contains integers to increase simulation runtime */
FastDeck::FastDeck() 
{
    for (int i = 1; i <= 13; ++i) {
        for (int j = 0; j < 4*DECK_MULT; ++j) {
            if (i >= 11) {
                cardValues.push_back(10); // Face cards have a value of 10
            }
            else {
                cardValues.push_back(i);  // Number cards retain their value
            }
        }
    }
    shuffle(); // This should only be done here and in replenish as this deck can be very large
}

std::vector<int>& FastDeck::getCardValues() {
    return cardValues;
}

void FastDeck::shuffle()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(cardValues.begin(), cardValues.end(), gen);
}

int FastDeck::dealCard()
{
    if(!cardValues.empty()) 
    {
        int card = cardValues.front(); // Get the first card's value
        cardValues.erase(cardValues.begin()); // Remove the first card
        return card;
    } else { // If the deck is empty, replenish it and then recall the method as intended
        this->replenish();
        return dealCard();
    }
}

// Refills the deck to its original size
void FastDeck::replenish()  
{
    cardValues.clear();

    for (int i = 1; i <= 13; ++i) {
        for (int j = 0; j < 4*DECK_MULT; ++j) {
            if (i >= 11) {
                cardValues.push_back(10); // Face cards have a value of 10
            }
            else {
                cardValues.push_back(i); // Number cards retain their value
            }
        }
    }
    shuffle(); // Reshuffle the newly refilled deck
}

void FastDeck::printDeck()
{
    for (const auto& value : cardValues) {
        std::cout << value << ", ";
    }
    std::cout<< std::endl;
}

int FastDeck::getCardValueFromIndex(int index) const {
    if (index < 0 || index >= cardValues.size()) {
        throw std::out_of_range("Invalid index");
    }
    return cardValues[index];
}
