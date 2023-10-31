#include "Card.h"
#include <iostream>
#include <stdexcept>

Card::Card() {}

Card::Card(int cardNum, char suit) : cardNum(cardNum), suit(suit) {}

void Card::setCardNum(int cardNum) {
    this->cardNum = cardNum;
}

void Card::setSuit(char suit) {
    this->suit = suit;
}

int Card::getCardNum() const {
    return this->cardNum;
}

int Card::getCardValue() const 
{
    int c = this->cardNum;

    if (c == 1) return 11; // Ace
    else if (c >= 2 && c <= 10) return c; // 2-10
    else if (c >= 11 && c <= 13) return 10; // Face cards
    else throw std::runtime_error("Invalid card number");
}

char Card::getSuit() const {
    return this->suit;
}

void Card::printCard() const {
    std::cout << this->cardNum << this->suit << ", ";
}
