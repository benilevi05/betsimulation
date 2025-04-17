/*
Roulette Betting Strategy Simulation
I created this code to simulate a roulette in to test a strategy for betting.
The strategy in question is to bet a percentage of your total money. This means everytime your money goes up you bet more.
The specific betting of the roulette is betting a dolar to 6 numbers each to cover 30 numbers.
This means there is a high chance of winning but a low payout. I wanted to test how this works with the betting strategy in question.
The results are as follows when given a starting amount of 100 dollars, betting 10% of the total money, in 100 rounds:
1. The total money that is left is on average -20% of the starting money you bet.
2. The chance of going bankrupt is low (less than 2-3%).
3. The chance of losing money is high (about 75%).

At the start even if you win a lot of times in a row, when you lose the loss is much more than you gain.
Since the total bet amount goes up with the total money, the wins at the start become much negligible compared to losses later.abort
This means even when you get luckier than average with a lot of wins, you still might lose money.
In conlusion, the strategy of betting a percentage of your total money doesn't seem to be good for low risk roulette.
Created by Beni
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int moneyAllLost = 0;
static float totalGains = 0;
static int timesWon = 0;
static int timesLost = 0;
static float totalMoneyOverall = 0;

// Given the total money, determines the bet amount.
int betAmount(float totalMoney) {
    int betAmount = (int)(totalMoney / 10);
    if (betAmount < 5) {
        betAmount = 5;
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

    for (int i = 0; i < numRounds; i++) {
        int betAmountValue = betAmount(totalMoney);
        totalMoney -= betAmountValue;
        if (totalMoney <= 0) {
            printf("You are out of money!\n");
            moneyAllLost += 1;
            break;
        }
        printf("Round %d: Betting $%d\n", i + 1, betAmountValue);
        float winnings = betRoulette(betAmountValue);
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