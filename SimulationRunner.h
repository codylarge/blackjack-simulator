#ifndef SIMULATIONRUNNER_H
#define SIMULATIONRUNNER_H

#include "FastDeck.h"  // Include the header file for the Deck class

class SimulationRunner 
{
private:
    int simulations; // Variable to store the number of simulations
    FastDeck deck;       // Using the Deck class

public:
    SimulationRunner(int simulations);

    void run();
    void initSimulation(std::vector<int>& dealerHand, int& playerHit, bool& aceInPlay);
    int simulateDealerHand(int dealerHandTotal, int hitCard, bool aceInPlay);
    bool checkForAce(std::vector<int>& dealerHand);
};

#endif // SIMULATIONRUNNER_H
