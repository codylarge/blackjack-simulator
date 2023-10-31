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
        // These are the only 3 variables we need to run the simulation
        std::vector<int> dealerHand;
        bool aceInPlay = false;
        int playerHit;
        
        // Initialize above variables
        initSimulation(dealerHand, playerHit, aceInPlay);

        int dealerStartingHandTotal = std::accumulate(dealerHand.begin(), dealerHand.end(), 0);

        int dealerTotalWithPlayerHit = simulateDealerHand(dealerStartingHandTotal, deck.dealCard(), aceInPlay); // Run simulation assuming 3rd base player HIT
        int dealerTotalWithoutPlayerHit = simulateDealerHand(dealerStartingHandTotal, playerHit, aceInPlay); // Run simulation assuming 3rd base player STAYED

        //std::cout << "\nWith Player Hit: " << dealerTotalWithPlayerHit << ", Without: " << dealerTotalWithoutPlayerHit; // Uncomment to look at both hand results


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
        else // Player hit/stay has same outcome
        {
            neither++;
        }
    }

    // Print totals
    std::cout << "\nDealers saved by hit: " << saves << "\nDealers screwed by hit: " << busts << "\nDealers uneffected by hit: " << neither;
}

// Play the dealers hand until they have over 16. Returns the total after hand is played
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
            dealerHandTotal -= 10; // dealer was REQUIRED to revert ace value 11 -> 1

            if (dealerHandTotal > 16) // This will only happen if dealer had a 16 and hit an ace (16 -> 27 -> 17 -> turn over)
                return dealerHandTotal;
        }
    }
        
    if (hitCard == 1) aceInPlay = true;

    simulateDealerHand(dealerHandTotal + hitCard, deck.dealCard(), aceInPlay); // Re-call with new total and next hit card
}


// Fills dealers hand, simulates player hit, and checks for starting aces in dealers hand
void SimulationRunner::initSimulation(std::vector<int>& dealerHand, int& playerHit, bool& aceInPlay)
{
    for (int j = 0; j < 2; ++j) // Fill dealers starting hand
    {
        int dealerCard = deck.dealCard();
        dealerHand.push_back(dealerCard);
    }
    playerHit = deck.dealCard(); // Simulate players hit
    aceInPlay = checkForAce(dealerHand); // Check for aces
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
