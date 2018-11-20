#pragma once
#include <iostream>
#include "Strategy.h"
using namespace std;

class StrategyAggressive : public Strategy {
public:
    StrategyAggressive(Player* inputPlayer);
    //~StrategyAggressive();  //no destructor needed as no data is owned by the strategy and the player is hanedled by the UI
    void attack();
    void reinforce();
    void fortify();

};
