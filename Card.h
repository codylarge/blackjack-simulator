#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <stdexcept>

class Card 
{
private:
    int cardNum;
    char suit;

public:
    Card();
    Card(int cardNum, char suit);
    void setCardNum(int cardNum);
    void setSuit(char suit);
    int getCardNum() const;
    int getCardValue() const;
    char getSuit() const;
    void printCard() const;
};

#endif // CARD_H
