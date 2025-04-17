/*
Testing for the strategy to go higher when loss in low rist roulette.
The results are much worse than the previous one.
When given a starting amount of 100 dollars, betting 10 dollars, doubling when lost, in 100 rounds.
Total money left is on average -30% of the starting money you bet.
The chance of going bankrupt is high (about 30%).
When quadruppling the bet when lost, the chance of going bankrupt is even higher (about 50%) and gains is even lower (about -40%).
This implies that the strategy itself is flawed for low rist roulette.
Created by Beni
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int moneyAllLost = 0;
float totalGains = 0;
int timesWon = 0;
int timesLost = 0;
float totalMoneyOverall = 0;
const int PER_ROUND_BET_AMOUNT = 10;

// Given the previous result, determines the bet amount.
int betAmount(float previousResult) {
    int betAmount = 0;
    if (previousResult > 0) {
        betAmount = PER_ROUND_BET_AMOUNT;
    } else {
        betAmount = PER_ROUND_BET_AMOUNT * 2;
    }
    return betAmount;
}

// Returns the money won given bet amount. Returns 0 if lost.
float betRoulette(int betAmount) {
    float betTemp = betAmount;
    int randomNum = rand() % 37;
    if (randomNum >= 7) {
        return betTemp + betTemp / 5;
    } else {
        return 0;
    }
}

void playGame(float startMoney, int numRounds) {
    float totalMoney = startMoney;
    float winnings = 1; // Initialize winnings to a non-zero value to enter the loop

    for (int i = 0; i < numRounds; i++) {
        int betAmountValue = betAmount(winnings);
        totalMoney -= betAmountValue;
        if (totalMoney <= 0) {
            printf("You are out of money!\n");
            moneyAllLost += 1;
            break;
        }
        printf("Round %d: Betting $%d\n", i + 1, betAmountValue);
        winnings = betRoulette(betAmountValue);
        if (winnings > 0) {
            totalMoney += winnings;
            printf("You won $%.2f! Total money: $%.2f\n", winnings, totalMoney);
        } else {
            printf("You lost! Total money: $%.2f\n", totalMoney);
        }
    }

    totalGains += (totalMoney - startMoney) / startMoney * 100;
    totalMoneyOverall += totalMoney;

    if (totalMoney >= startMoney) {
        printf("You finished with $%.2f, which is a profit!\n", totalMoney);
        timesWon += 1;
    } else {
        printf("You finished with $%.2f, which is a loss.\n", totalMoney);
        timesLost += 1;
    }
}

int main(int argc, char* argv[]) {
    int simulationCount = 100;
    float betAmount = 100.0;
    srand(time(NULL));
    for (int i = 0; i < simulationCount; i++) {
        printf("Simulation %d:\n", i + 1);
        playGame(betAmount, 100);
        printf("Total gains: %.2f%%\n", totalGains / (i + 1));
        printf("Times won: %d\n", timesWon);
        printf("Times lost: %d\n", timesLost);
        printf("Money all lost: %d times\n", moneyAllLost);
        printf("Total Money Bet Amount: $%.2f\n", betAmount * (i + 1));
        printf("Total Money Left: $%.2f\n", totalMoneyOverall);
    }
}