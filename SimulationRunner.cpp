#include "SimulationRunner.h"
#include "FastDeck.h" 
#include <iostream>
#include <numeric>

SimulationRunner::SimulationRunner(int simulations) : simulations(simulations) {}

void SimulationRunner::run() 
{
    int saves = 0, busts = 0, neither = 0;
    // Player hit saves dealer, player hit cause dealer to bust, player hit has no effect

    for (int i = 0; i < simulations; ++i) 
    {
        deck.shuffle();

        std::vector<int> dealerHand;
        bool aceInPlay = false;
        int playerHit;
        
        initSimulation(dealerHand, playerHit, aceInPlay);

        int dealerStartingHandTotal = std::accumulate(dealerHand.begin(), dealerHand.end(), 0);

        int dealerTotalWithPlayerHit = simulateDealerHand(dealerStartingHandTotal, deck.dealCard(), aceInPlay);
        int dealerTotalWithoutPlayerHit = simulateDealerHand(dealerStartingHandTotal, playerHit, aceInPlay);

        
        //std::cout << "\nWith Player Hit: " << dealerTotalWithPlayerHit << ", Without: " << dealerTotalWithoutPlayerHit; // Uncomment to look at both hands

        if ((dealerTotalWithoutPlayerHit > 21 && dealerTotalWithPlayerHit <= 21)) // Players hit saved the dealer
        {
            saves++;
            std::cout << "\tsave";
        }
        else if (dealerTotalWithoutPlayerHit <= 21 && dealerTotalWithPlayerHit > 21) // Players hit caused the dealer to bust
        {
            busts++;
            std::cout << "\tbust";
        }
        else // no difference
        {
            neither++;
        }
    }
    std::cout << "\nDealers saved by hit: " << saves << "\nDealers screwed by hit: " << busts << "\nDealers uneffected by hit: " << neither;
}

int SimulationRunner::simulateDealerHand(int dealerHandTotal, int hitCard, bool aceInPlay) // Recursive method, calls itself with next hitCard until bust, or 17+
{
    if (dealerHandTotal > 16)
    {
        if (!aceInPlay || dealerHandTotal <= 21)
        {
            return dealerHandTotal; // Dealer is done hitting
        }
        else // ace must be in play AND dealer must be bust at this point
        {
            dealerHandTotal -= 10;

            if (dealerHandTotal > 16) 
                return dealerHandTotal;
        }
    }
        
    if (hitCard == 1) aceInPlay = true;

    simulateDealerHand(dealerHandTotal + hitCard, deck.dealCard(), aceInPlay); // Re-call with new total and next hit card
}

void SimulationRunner::initSimulation(std::vector<int>& dealerHand, int& playerHit, bool& aceInPlay)
{
    for (int j = 0; j < 2; ++j) // Fill dealers starting hand
    {
        int dealerCard = deck.dealCard();
        dealerHand.push_back(dealerCard);
    }
    playerHit = deck.dealCard(); // Simulate players hit
    aceInPlay = checkForAce(dealerHand);
}


/* Utility */
bool SimulationRunner::checkForAce(std::vector<int>& dealerHand) {
    for (int card : dealerHand) {
        if (card == 1) {
            return true; // Ace found
        }
    }
    return false; // No ace found
}
