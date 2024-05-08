#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"

class Merkelmain
{
public:
    Merkelmain();
    /** Call this to start the sim */
    [[noreturn]]void init();
private:
    void printMenu();
    void printHelp();
    void printHelpCmd(std::string& cmd);
    void printMarketStats();
    void printMin(std::vector<std::string> const& tokens);
    void printMax(std::vector<std::string> const& tokens);
    void printAvg(std::vector<std::string> const& tokens);
    void printPrediction(std::vector<std::string> const& tokens);
    void gotoNextTimeframe();
    void gotoPrevTimeframe();
    void processUserInput();

    std::string currentTime;

    OrderBook orderBook{ "data.csv" };

};

