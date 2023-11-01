#include "SimulationRunner.h"
#include "FastDeck.h" 
#include <iostream>
#include <numeric>

SimulationRunner::SimulationRunner(int simulations) : simulations(simulations) {}

void SimulationRunner::run()
{
    /* Variables declared outside loop will be analysed after loop */
    int neither = 0;
    // These 2 variables are used to see if the dealers starting hand will change 3rd base hitting effect.
    std::vector<int> saveHands(15, 0); // Technically 2 & 3 are impossible to get as starting hands but its easier to include them
    std::vector<int> bustHands(15, 0); // 

    for (int i = 0; i < simulations; ++i)
    {
        std::vector<int> dealerStartingHand;
        bool aceInPlay = false;
        int playerHit;

        // Initialize above variables
        initSimulation(dealerStartingHand, playerHit, aceInPlay);

        int dealerStartingHandTotal = std::accumulate(dealerStartingHand.begin(), dealerStartingHand.end(), 0); 

        int dealerTotalWithPlayerHit = simulateDealerHand(dealerStartingHandTotal, deck.dealCard(), aceInPlay); // Run simulation assuming 3rd base player HIT
        int dealerTotalWithoutPlayerHit = simulateDealerHand(dealerStartingHandTotal, playerHit, aceInPlay); // Run simulation assuming 3rd base player STAYED

        if (dealerStartingHandTotal >= 2 && dealerStartingHandTotal <= 21) {
            if ((dealerTotalWithoutPlayerHit > 21 && dealerTotalWithPlayerHit <= 21)) {
                saveHands[dealerStartingHandTotal - 2]++;
                //std::cout << "\tsave";
            }
            else if (dealerTotalWithoutPlayerHit <= 21 && dealerTotalWithPlayerHit > 21) {
                bustHands[dealerStartingHandTotal - 2]++;
                //std::cout << "\tbust";
            }
            else {
                neither++;
            }
        }
        else {
            // SHould never happen
            std::cout << "Dealer hand total is out of range.";
        }
    }

    printResults(saveHands, bustHands, neither);
}

void SimulationRunner::printResults(std::vector<int>& saveHands, std::vector<int>& bustHands, int& neither)
{
    // Print numeric totals
    /*std::cout << "\nDealers saved by hit: " << std::accumulate(saveHands.begin(), saveHands.end(), 0)
        << "\nDealers busted by hit: " << std::accumulate(bustHands.begin(), bustHands.end(), 0)
        << "\nDealers unaffected by hit: " << neither;
        */

    int handTotalWithMaxDiscrepancy = -1;
    double largestDiscrepancy = 0.0;

    // Print the results of every dealer starting hand (Seems completely random)
    for (int i = 0; i < saveHands.size(); ++i) {
        double totalSaves = saveHands[i] + bustHands[i];
        if (totalSaves != 0) {
            double savePercentage = (static_cast<double>(saveHands[i]) / totalSaves) * 100; // Get the % of time this dealerHandTotal saved the dealer
            double bustPercentage = (static_cast<double>(bustHands[i]) / totalSaves) * 100;// Get the % of time this dealerHandTotal busted the dealer
           // 
            double discrepancy = (std::abs(savePercentage - bustPercentage))/2;
            if (discrepancy > largestDiscrepancy) 
            {
                largestDiscrepancy = discrepancy;
                handTotalWithMaxDiscrepancy = i + 2; // Considering hand total from 2 to 16
            }
        }
    }

    // Calculate total saves, busts, and total actions
    int totalSaves = std::accumulate(saveHands.begin(), saveHands.end(), 0);
    int totalBusts = std::accumulate(bustHands.begin(), bustHands.end(), 0);
    int totalActions = totalSaves + totalBusts + neither;

    // Calculate percentages
    double savePercentage = (static_cast<double>(totalSaves) / (totalSaves + totalBusts)) * 100;
    double bustPercentage = (static_cast<double>(totalBusts) / (totalSaves + totalBusts)) * 100;
    double neitherPercentage = (static_cast<double>(neither) / totalActions) * 100;


    //largestDiscrepancy = std::abs(savePercentage - bustPercentage); // 
    std::string resultWithLargestDiscrepancy = (savePercentage > bustPercentage) ? "save" : "bust"; // Find out if largest descrepancy was a save or a bust
    // Print percentages
    std::cout << "Player hit had no effect " << neitherPercentage << "% of the time" << std::endl;
    std::cout << "Out of the times it did have an effect..." << std::endl;
    std::cout << "Player hit saved the dealer " << savePercentage << "% of the time" << std::endl;
    std::cout << "Player hit caused the dealer to bust " << bustPercentage << "% of the time" << std::endl;

    std::cout << "Dealer starting hand of " << handTotalWithMaxDiscrepancy << " had the largest discrepancy with a save percentage of " << savePercentage << "% & a bust percentage " << bustPercentage << "%" << std::endl;
    std::cout << "\n\n\n\tCONCLUSION\n" << "3rd base hit hurts the table";
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
