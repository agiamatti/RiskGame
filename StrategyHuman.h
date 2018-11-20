#pragma once
#include <iostream>
#include "Strategy.h"
using namespace std;

class StrategyHuman :public Strategy {
public:
    StrategyHuman(Player* inputPlayer);
    //~StrategyHuman(); //no destructor needed as no data is owned by the strategy and the player is hanedled by the UI
    void attack();
    void reinforce();
    void fortify();

};
